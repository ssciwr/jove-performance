#ifndef LIBJOVE_VAULT_MP2_H
#define LIBJOVE_VAULT_MP2_H

#include <iostream>
#include <armadillo>
#include "../grid/jove_grid.h"
#include <string>

namespace libjove{

        class vault_mp2 {
                private: 
                        bool mScale;
                        bool mTransform;
                        bool mCoulNeg;
                        bool mIntegralSampling;
                        size_t mrtype;
                        size_t mrsize;
                        bool mrcutoff;
                        size_t mttype;
                        size_t mtsize;
                        double mttol;
                        bool mExportMat;
                        size_t mPrintLevel;

                        size_t mocc;
                        size_t mvirt;
                        size_t mnmo;
                        size_t mnbsf;

                        arma::mat mf_mat;
                        arma::mat mc_mat;
                        arma::mat mcgto_mat;
                        arma::cube mcoulomb;
                        jove_grid mrgrid;
                        jove_grid mtgrid;

                public: 
                        vault_mp2() : mScale(0), mTransform(0), mCoulNeg(0),
                            mIntegralSampling(0), mrtype(1), mrsize(20000038), 
                            mrcutoff(0), mttype(1), mtsize(4), mttol(10e-14), 
                            mExportMat(0), mPrintLevel(1), mocc(1), mvirt(1), mnmo(2),
                            mnbsf(2)
                            {       mf_mat.zeros(mnbsf, mnbsf);
                                    mc_mat.zeros(mnbsf, mnmo);
                                    mcgto_mat.zeros(mrsize, mnbsf);
                                    mcoulomb.zeros(mnbsf, mnbsf, mrsize);
                                    load_check();};

                        vault_mp2 (bool Scale, bool Transform, bool CoulNeg, 
                                        bool IntegralSampling, size_t rtype,
                                        size_t rsize, bool rcutoff, size_t ttype, 
                                        size_t tsize, double ttol, bool ExportMat, 
                                        size_t PrintLevel, size_t occ, size_t virt, 
                                        size_t nmo, size_t nbsf) :
                                mScale(Scale), mTransform(Transform), mCoulNeg(CoulNeg),
                                mIntegralSampling(IntegralSampling), mrtype(rtype), 
                                mrsize(rsize), mrcutoff(rcutoff), mttype(ttype), 
                                mtsize(tsize), mttol(ttol), mExportMat(ExportMat),
                                mPrintLevel(PrintLevel), mocc(occ), mvirt(virt), mnmo(nmo),
                                mnbsf(nbsf)
                                {
                                   mf_mat.zeros(mnbsf, mnbsf);
                                    mc_mat.zeros(mnbsf, mnmo);
                                    mcgto_mat.zeros(mrsize, mnbsf);
                                    mcoulomb.zeros(mnbsf, mnbsf, mrsize);
                                        load_check();};
                        
                        void load (bool Scale, bool Transform, bool CoulNeg, 
                                        bool IntegralSampling, size_t rtype,
                                        size_t rsize, bool rcutoff, size_t ttype, 
                                        size_t tsize, double ttol, bool ExportMat, 
                                        size_t PrintLevel, size_t occ, size_t virt, 
                                        size_t nmo, size_t nbsf, arma::mat f_mat, 
                                        arma::mat c_mat, arma::mat cgto_mat, arma::cube coulomb,
                                        jove_grid rgrid, jove_grid tgrid);

                        void load_check (); 

                        bool get_mScale () {return mScale;};
                        bool get_mTransform () {return mTransform;};
                        bool get_mCoulNeg () {return mCoulNeg;};
                        bool get_mIntegralSampling () {return mIntegralSampling;};
                        size_t get_mrtype () {return mrtype;};
                        size_t get_mrsize () {return mrsize;};
                        bool get_mrcutoff () {return mrcutoff;};
                        size_t get_mttype () {return mttype;};
                        size_t get_mtsize () {return mtsize;};
                        double get_mttol () {return mttol;};
                        bool get_mExportMat () {return mExportMat;};
                        size_t get_mPrintLevel () {return mPrintLevel;};

                        size_t get_mocc () {return mocc;};
                        size_t get_mvirt () {return mvirt;};
                        size_t get_mnmo () {return mnmo;};
                        size_t get_mnbsf () {return mnbsf;};

                        arma::mat get_mf_mat() {return mf_mat;};
                        arma::mat get_mc_mat() {return mc_mat;};
                        arma::mat get_mcgto_mat() {return mcgto_mat;};
                        arma::cube get_mcoulomb() {return mcoulomb;};

                        jove_grid get_rgrid(){return mrgrid;};
                        jove_grid get_tgrid(){return mtgrid;};

                        bool export_toFile (std::string folder);

        };


} //namespace libjove

#endif //LIBJOVE_VAULT_BASE
