#include "loader_mp2_fromfile.h"
#include "../grid/jove_grid.h"

namespace libjove{

        void loader_mp2_fromfile::perform (std::string folder, vault_mp2 &vault){

                arma::vec inputs;
                inputs.load(folder+"inputs.vec");

                arma::mat f_mat;
                f_mat.load(folder+"f.mat");
                
                arma::mat c_mat;
                c_mat.load(folder+"c.mat");

                arma::mat cgto_mat;
                cgto_mat.load(folder+"cgto.mat");

                arma::cube coulomb;
                coulomb.load(folder+"coulomb.cube");

                arma::mat rpts;
                rpts.load(folder+"rpts.mat");
                arma::mat rwts;
                rwts.load(folder+"rwts.mat");
                jove_grid rgrid(rpts, rwts, rpts.n_cols, 1);

                arma::mat tpts;
                tpts.load(folder+"tpts.mat");
                arma::mat twts;
                twts.load(folder+"twts.mat");
                jove_grid tgrid(tpts, twts, tpts.n_cols, 1);

                vault.load(inputs(0), inputs(1), inputs(2), inputs(3), inputs(4), inputs(5),
                        inputs(6), inputs(7), inputs(8), inputs(9), inputs(10),
                        inputs(11), inputs(12), inputs(13), inputs(14), inputs(15),
                        f_mat, c_mat, cgto_mat, coulomb, rgrid, tgrid);

        }//loader_mp2_fromfile

}//namespace libjove
