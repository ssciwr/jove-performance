#ifndef LIBJOVE_JOVE_GRID_C
#define LIBJOVE_JOVE_GRID_C

#include "jove_grid.h"
#include <iostream>

namespace libjove{

        void jove_grid::init_3d_grid(arma::mat &mat_pts, arma::mat &mat_wts){
                init_3d_grid_standalone(mat_pts, mat_wts);
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

        void jove_grid::init_grid(int gridTypeT){

                gridType=gridTypeT; 

                if (gridTypeT==1){ 
                        init_3d_grid(mgpts, mgwts);
                }else{ 
                        //Throw exception
                }


        }//init grid for r grid

        void jove_grid::init_1d_grid(arma::mat &mat_pts, arma::mat &mat_wts){
                init_1d_grid_standalone(mat_pts, mat_wts);
        }//init_1d_grid

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
