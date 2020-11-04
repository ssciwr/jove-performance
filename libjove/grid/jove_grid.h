#ifndef LIBJOVE_JOVE_GRID_H
#define LIBJOVE_JOVE_GRID_H

//gauss-legendre for t grid
#include "../utils/3rd_party/gauss_legendre.h"
#include <iostream>
#include <armadillo>


namespace libjove{
        /** \brief Class for handling the different quadrature grids.
            
            In this class we define and initialize the different quadrature grid objects. 
            Points and weights are stored in armadillo matrices. 

            \ingroup libjove
         **/

        class jove_grid  {
                private: 
                        arma::mat mgpts; //!< matrix of grid points
                        arma::mat mgwts; //!< matrix of grid point weights for quadrature

                        size_t gridSize; //!<grid size, e.g. number of points per...

                        int gridType; //!< grid type, e.g. STD-1 Grid, Gauss-Legendre...
                public: 
                        jove_grid() : gridSize(0), gridType(99) {
                        } //!< construktor initializing the default values

                        /** \brief Construktor for directly initializing a grid through matrices
                         * This constructor will generate and load a grid from given matrices
                         **/
                        jove_grid(arma::mat gpts, arma::mat gwts, size_t size, int type) : 
                                mgpts(gpts), mgwts(gwts), gridSize(size), gridType(type) {};

                        jove_grid (const jove_grid &grid1) {
                                mgpts = grid1.mgpts;
                                mgwts = grid1.mgwts;
                                gridSize = grid1.gridSize;
                                gridType = grid1.gridType;
                        }

                        /** \brief initialization function for the spacial grids
                         * Here begin overloaded functions for the different grids we will use
                          First is the spacial grid, which will be provided by libdftn/MoleGrid at first
                          This function creates the grid and loads the pointer with the Address. 

                          \param[in] gridTypeT int : 1 orders the libdftn/MoleGrid implementation 
                          which uses the XC_GRID input variable from qchem

                        */ 
                        void init_grid(int gridTypeT);

                        /** \brief Grid for t quadratur, right now only Gauss-Legendre is implemented
                         * This function creates the grid and loads the pointer with the address. 
                         *
                         * 
                         *\param[in] gridTypeT int : 99 for uninialized see above, 11 for Gauss-Legendre
                         *                  from gauss-legendre.c
                         * \param[in] gridSizeT size_t : Number of Points on this grid, 0 means unitialized
                         * */
                        void init_grid(int gridTypeT, size_t gridSizeT, double a, double b, double Tol);

                        /** \brief Hand back the address of our grid as pointers
                         *
                         * */

                        void get_grid(double *&jpts, double *&jwts){
                                jpts=mgpts.memptr();
                                jwts=mgwts.memptr();
                        }

                        size_t get_gridSize() {return gridSize;}
                        int get_gridType() {return gridType;}

                        arma::mat get_mgpts() {return mgpts;}
                        arma::mat get_mgwts() {return mgwts;}


            private:
                        void init_3d_grid(arma::mat &mat_pts, arma::mat &mat_wts);
                        void init_3d_grid_standalone(arma::mat &mat_pts, arma::mat &mat_wts);
                        void init_3d_grid_qchem(arma::mat &mat_pts, arma::mat &mat_wts);

                        void init_1d_grid(arma::mat &mat_pts, arma::mat &mat_wts);
                        void init_1d_grid_standalone(arma::mat &mat_pts, arma::mat &mat_wts);
                        void init_1d_grid_qchem(arma::mat &mat_pts, arma::mat &mat_wts);

        }; //jove_grid class


}//libjove namespace

#endif //LIBJOVE_JOVE_GRID_H
