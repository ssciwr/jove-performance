#ifndef LIBJOVE_JOVE_GRID_C
#define LIBJOVE_JOVE_GRID_C

#include "jove_grid.h"
#include <iostream>
//#include <adcman/adcman/adcman_exceptions.h>

#ifdef QCHEM
#include <libdftn/xcclass.h>
#endif


namespace libjove{
//        using namespace adcman;

        void jove_grid::init_3d_grid(arma::mat &mat_pts, arma::mat &mat_wts){
#ifdef QCHEM
                init_3d_grid_qchem(mat_pts, mat_wts); 
#endif
#ifndef QCHEM
                init_3d_grid_standalone(mat_pts, mat_wts);
#endif
        }//init_3d_grid

        void jove_grid::init_3d_grid_standalone(arma::mat &mat_pts, arma::mat &mat_wts){
                int npts = 1;
                gridSize = npts;
                mat_pts.zeros(3, gridSize);
                mat_wts.zeros(0, gridSize);
                for (int i=0; i<gridSize; i++){
                        mat_pts(0,i) = 0.0;
                        mat_pts(1,i) = 0.0;
                        mat_pts(2,i) = 0.0;

                        mat_wts(0,i) = 0.0;
                }//for

        }//init_3d_grid_standalone

        void jove_grid::init_3d_grid_qchem(arma::mat &mat_pts, arma::mat &mat_wts){
#ifdef QCHEM
                XCAtoms xcatom; 
                int jobID0 = 0; 
                XCFunctional Func(0,0); 
                XCJobPara xcpara(Func, xcatom, jobID0);
                double thresh = xcpara.thresh; 
                int nAtoms = xcatom.getNAtoms();

                int grdTyp = rem_read(REM_IGRDTY);

                int IBCode = rem_read(REM_IBASIS);
                SET_QC_FCOMMON(&IBCode); 
                
                XCBasisSet basDen(IBCode, nAtoms, thresh); 
                xcatom.setSize(basDen); 

                MoleGrid mgrid(xcatom, grdTyp, xcpara.nDrvNuc, thresh);

                int *iPtBat= new int[mgrid.getNBatch()+1]; 
                int npts=mgrid.getNPts();
                gridSize=npts; 
                int nbatch=mgrid.getNBatch();

                mat_pts.zeros(3,gridSize);
                mat_wts.zeros(1,gridSize);

                mgrid.getMolGrid(mat_pts.memptr(), mat_wts.memptr(), iPtBat, npts, nbatch); 

                delete[] iPtBat; 
#endif
        }//init_3d_grid_qchem

        void jove_grid::init_grid(int gridTypeT){

                gridType=gridTypeT; 

                if (gridTypeT==1){ 
                        init_3d_grid(mgpts, mgwts);
                }else{ 
                        //Throw exception
                }


        }//init grid for r grid

        void jove_grid::init_1d_grid(arma::mat &mat_pts, arma::mat &mat_wts){
#ifdef QCHEM
                init_1d_grid_qchem(mat_pts, mat_wts);
#endif
#ifndef QCHEM
                init_1d_grid_standalone(mat_pts, mat_wts);
#endif
        }//init_1d_grid

        void jove_grid::init_1d_grid_qchem(arma::mat &mat_pts, arma::mat &mat_wts){
                        int m=(gridSize+1)>>1; 
                        double gl_pts[m]; 
                        double gl_wts[m];

                        double *ptr_pts=gl_pts; 
                        double *ptr_wts=gl_wts; 

                        gauss_legendre_tbl(gridSize, ptr_pts, ptr_wts, 10e-14);
                        double a=0;
                        double b=1;

                        double A=0.5*(b-a);
                        double B=0.5*(a+b);

                        mat_pts.zeros(1,gridSize);
                        mat_wts.zeros(1,gridSize);

                        if (gridSize%2==0) { 
                                for (int i=0; i<(gridSize/2); i++){
                                        mat_pts(0,i)=A*(-gl_pts[i])+B;
                                        mat_pts(0,gridSize-1-i)=A*gl_pts[i]+B;

                                        mat_wts(0,i)=A*gl_wts[i];
                                        mat_wts(0,gridSize-1-i)=A*gl_wts[i];
                                }//for
                        }// if even

                        if(gridSize%2!=0){
                                mat_pts(0,((gridSize+1)/2-1))=A*gl_pts[0]+B;
                                mat_wts(0,((gridSize+1)/2-1))=A*gl_wts[0];

                                for (int i=0; i<((gridSize-1)/2); i++){
                                        mat_pts(0,i)=A*(-gl_pts[i])+B;
                                        mat_pts(0,gridSize-1-i)=A*gl_pts[i]+B;

                                        mat_wts(0,i)=A*gl_wts[i];
                                        mat_wts(0,gridSize-1-i)=A*gl_wts[i];

                                }//for
                        }//if odd

        }//init_1d_grid_qchem

        void jove_grid::init_1d_grid_standalone(arma::mat &mat_pts, arma::mat &mat_wts){
    
        }//init_1d_grid_standalone

        void jove_grid::init_grid(int gridTypeT, size_t gridSizeT, double a, double b, double Tol){
                gridType=gridTypeT; 
                gridSize=gridSizeT;

                if (gridType==1){ //Gauss-Legendre
                        init_1d_grid(mgpts, mgwts);

                }else{ //if g-l
                        //thro exception
                }//else

        }//init grid for t grid


} //namespace libjove

#endif //LIBJOVE_JOVE_GRID_C
