#include "do_mp2.h"
#include <iostream>
#include "../grid/jove_grid.h"
#include <armadillo>
//#include "../integrals/jove_vmul.h"
#include "../utils/ttimer.h"
#include "../utils/pprinter.h"
#include <Eigen/Eigen>
#include <omp.h>

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
                // transpose so we are iterating over the inner index to reduce cache misses
                arma::inplace_trans(o_i_p_k);
                arma::inplace_trans(v_a_p_k);

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

                // pre-calculate t factors
                std::vector<Eigen::VectorXd> teps_o(tsize, Eigen::VectorXd(occ));
                std::vector<Eigen::VectorXd> teps_v(tsize, Eigen::VectorXd(virt));
                std::vector<Eigen::MatrixXd> teps_c;
                teps_c.reserve(tsize);
                for (int k = 0; k < tsize; k++){
                        for (int i = 0; i < occ; i++){
                            teps_o[k][i] = pow((double)tpts(0,k), (double) (- f_mat(i,i)));
                        }//for i

                        for (int a = 0; a < virt; a++){
                            int pos_f = a + occ;
                            teps_v[k][a] = pow((double)tpts(0,k),
                                            (double) (f_mat(pos_f, pos_f)));
                        }//for a

                        double inv_t = 1.0/(double)tpts(0,k);
                        teps_c.push_back(teps_o[k]*teps_v[k].transpose()*inv_t);
                }

                using VecMap = const Eigen::Map<const Eigen::VectorXd>;
                using MatMap = const Eigen::Map<const Eigen::MatrixXd>;
                Eigen::VectorXd o_p;
                Eigen::VectorXd v_p;
                Eigen::MatrixXd c2_p;

#pragma omp parallel for reduction(+:e_mp2) schedule(dynamic) default(none) firstprivate(o_p, v_p, c2_p) shared(tsize, npts, occ, virt, twts, o_i_p_k, v_a_p_k, tcoulomb, teps_o, teps_v, teps_c) collapse(2)
                for (int k = 0; k < tsize; k++){
                        for (int p = 0; p < npts; p++){
                                // calculate t^x factors for this p & insert here - avoid copying everything
                                o_p = VecMap(o_i_p_k.colptr(p), occ).cwiseProduct(teps_o[k]);
                                v_p = VecMap(v_a_p_k.colptr(p), virt).cwiseProduct(teps_v[k]);
                                c2_p = MatMap(tcoulomb.slice_memptr(p), occ, virt).cwiseProduct(teps_c[k]);
                                for (int q = 0; q <= p; q++){
                                        // construct Eigen types that are const refs to the armadillo raw data
                                        VecMap o_q(o_i_p_k.colptr(q), occ);
                                        VecMap v_q(v_a_p_k.colptr(q), virt);
                                        MatMap c2_q(tcoulomb.slice_memptr(q), occ, virt);
                                        double jo=0;
                                        for (int a = 0; a < virt; a++){
                                                double tmp1 = o_p.dot(c2_q.col(a));
                                                double tmp2 = o_q.dot(c2_p.col(a));
                                                jo += tmp1 * tmp2;
                                        }//a
                                        // note: the above could be written as
                                        // double jo = ((c2_q.transpose()*o_p)).dot((c2_p.transpose()*o_q));
                                        // but the result is much slower than the explicit loop above
                                        double j = (c2_p.cwiseProduct(c2_q)).sum();
                                        double o = (o_p).dot(o_q);
                                        double v = (v_p).dot(v_q);
                                        double sum = (jo - 2 * j * o) * v;
                                        if(p!=q){
                                                sum *= 2.0;
                                        }
                                        e_mp2 += twts(0,k) * sum;
                                }//for q
                        }//for p
                        //out<<"  E_MP2: "<<e_mp2<<" with inc: "<<twts(0,k)*e_k<<" at t-Point, Weight "<<tpts(0,k)<<", "<<twts(0,k)<<" no."<<k+1<<"/"<<tsize<<std::endl;
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

