#include "do_mp2.h"
#include <iostream>
#include "../grid/jove_grid.h"
#include <armadillo>
//#include "../integrals/jove_vmul.h"
#include "../utils/ttimer.h"
#include "../utils/pprinter.h"

namespace libjove {


        
        void do_mp2::run (std::ostringstream &out, vault_mp2 &vault){
                std::ostringstream tmp_out;
                tmp_out << std::scientific;

                vault.export_toFile("./");

                pprinter drucker;
                drucker.prep_print(tmp_out);

                double energy = calc_mp2 (tmp_out, vault);
                
                drucker.print_mp2(vault, tmp_out);
                out<<std::scientific<<std::endl<<"  Final MP2 correction optained through JOVE: "<<energy<<std::endl;
                
                out << tmp_out.str();

        }//do_mp2::run
        
        double do_mp2 :: calc_mp2 (std::ostringstream &out, vault_mp2 &vault){
                
                int nmo = vault.get_mnmo();
                int occ = vault.get_mocc();
                int virt = vault.get_mvirt();

                arma::mat f_mat;
                f_mat = vault.get_mf_mat();
                arma::mat c_mat;
                c_mat = vault.get_mc_mat();
                arma::mat cgto_values;
                cgto_values = vault.get_mcgto_mat();
                arma::cube coulomb;
                coulomb = vault.get_mcoulomb();

                arma::mat rpts = vault.get_rgrid().get_mgpts();
                arma::mat rwts = vault.get_rgrid().get_mgwts();
                size_t npts= vault.get_rgrid().get_gridSize();

                arma::mat tpts = vault.get_tgrid().get_mgpts();
                arma::mat twts = vault.get_tgrid().get_mgwts();
                size_t tsize = vault.get_mtsize();

                cgto_values = cgto_values * c_mat;
                f_mat = c_mat.t() * f_mat * c_mat;

                
                arma::mat o_i_p_k = cgto_values.cols(0, occ-1);
                arma::mat v_a_p_k = cgto_values.cols(occ, nmo-1);

                arma::cube tcoulomb;
                tcoulomb.zeros(occ, virt, npts);

                //COULOMB MO TRANSFORMATION
                ttimer ttrans("Coulomb Trans");
                ttrans.start();
                for (int i=0; i<npts; i++){
                        tcoulomb.slice(i) = rwts(0,i) * c_mat.cols(0, occ-1).t() * 
                                (coulomb.slice(i)*c_mat.cols(occ, nmo-1));
                }
                ttrans.stop();
                
                double e_mp2 = 0;
                
                ttimer tmain("Main");
                tmain.start();

// #pragma omp parallel for                
                for (int k = 0; k < tsize; k++){
                //make copy of matrix and scale it
                        arma::mat o_i_p_k2 = o_i_p_k;
                        arma::mat v_a_p_k2 = v_a_p_k;
                        arma::cube coulomb2 = tcoulomb;
                        for (int i = 0; i < occ; i++){
                            o_i_p_k2.col(i) = o_i_p_k2.col(i) * 
                                    pow((double)tpts(0,k), (double) (- f_mat(i,i)/2));
                        }//for i

                        for (int a = 0; a < virt; a++){
                            int pos_f = a + occ;
                            v_a_p_k2.col(a) = v_a_p_k2.col(a) * pow((double)tpts(0,k),
                                                (double) (f_mat(pos_f, pos_f)/2));
                        }//for a
                

                        for (int i = 0; i < occ; i++){
                            for (int a = 0; a < virt; a++){
                                int pos_f = a + occ;
                                coulomb2.tube(i,a) = tcoulomb.tube(i,a) * 
                                    pow((double)tpts(0,k), (double) (f_mat(pos_f, pos_f)-f_mat(i,i)-1)/(2));
                            }//for a
                        }//for i

                        double e_k = 0;

                        // transpose so we are iterating over the inner index to reduce cache misses
                        arma::inplace_trans(o_i_p_k2);
                        arma::inplace_trans(v_a_p_k2);

                        for (int p = 0; p < npts; p++){
                                for (int q = 0; q < npts; q++){
                                        double jo=0;
                                        for (int a = 0; a < virt; a++){
                                                double tmp1 = 0;
                                                double tmp2 = 0;
                                                for (int i = 0; i < occ; i++){
                                                        tmp1 += o_i_p_k2(i,p) * coulomb2(i,a,q);
                                                }//for i
                                                for (int j = 0; j < occ; j++){
                                                        tmp2 += o_i_p_k2(j,q) * coulomb2(j,a,p);
                                                }//for j
                                                jo += tmp1 * tmp2;
                                        }//a
                                        double j = 0;
                                        for (int i = 0; i < occ; i++){
                                                for (int  a = 0; a < virt; a++){
                                                        j += coulomb2(i,a,p) * coulomb2(i,a,q);
                                                }//for a
                                        }//for i
                                        double o = 0;
                                        for (int i = 0; i < occ; i++){
                                                o += o_i_p_k2(i,p) * o_i_p_k2(i,q);
                                        }//for i 
                                        double v = 0;
                                        for (int a = 0; a < virt; a++){
                                                v += v_a_p_k2(a,p) * v_a_p_k2(a,q);
                                        }//for a
                                        e_k += (jo - 2 * j * o) * v;
                                }//for q
                        }//for p
                        e_mp2 += twts(0,k) * e_k;
                        out<<"  E_MP2: "<<e_mp2<<" with inc: "<<twts(0,k)*e_k<<" at t-Point, Weight "<<tpts(0,k)<<", "<<twts(0,k)<<" no."<<k+1<<"/"<<tsize<<std::endl;
                }//for k

                ttrans.print(out);
                tmain.stop();
                tmain.print(out);

                out << std::endl;
                out << "Summary of the characteristic sizes:" << std::endl;
                out << "tsize = " << tsize << std::endl;
                out << "npts = " << npts << std::endl;
                out << "occ = " << occ << std::endl;
                out << "virt = " << virt << std::endl;

                return e_mp2;
        }//calc_mp2

} //namespace libjove

