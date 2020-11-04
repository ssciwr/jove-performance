#include "vault_mp2.h"

namespace libjove {
        void vault_mp2::load_check(){

        }//load_check

        void vault_mp2::load (bool Scale, bool Transform, bool CoulNeg, 
                        bool IntegralSampling, size_t rtype,
                        size_t rsize, bool rcutoff, size_t ttype, 
                        size_t tsize, double ttol, bool ExportMat, 
                        size_t PrintLevel, size_t occ, size_t virt, 
                        size_t nmo, size_t nbsf, arma::mat f_mat, 
                        arma::mat c_mat, arma::mat cgto_mat, arma::cube coulomb,
                        jove_grid rgrid, jove_grid tgrid){
                mScale = Scale;
                mTransform = Transform;
                mCoulNeg = CoulNeg;
                mIntegralSampling = IntegralSampling;
                mrtype = rtype;
                mrsize = rsize;
                mrcutoff = rcutoff;
                mttype = ttype;
                mtsize = tsize;
                mttol = ttol;
                mExportMat = ExportMat;
                mPrintLevel = PrintLevel;
                mocc = occ;
                mvirt = virt;
                mnmo = nmo;
                mnbsf = nbsf;

                mf_mat.zeros(nbsf, nbsf);
                mf_mat = f_mat;

                mc_mat.zeros(nbsf, nmo);
                mc_mat = c_mat;

                mcgto_mat.zeros(rsize, nbsf);
                mcgto_mat = cgto_mat;

                mcoulomb.zeros(nbsf, nbsf, rsize);
                mcoulomb = coulomb;

                mrgrid = rgrid;
                mtgrid = tgrid;
            load_check();
        }//set

        bool vault_mp2::export_toFile (std::string folder){
                if (mExportMat){

                        arma::vec inputs(16);
                        inputs(0) = mScale;
                        inputs(1) = mTransform;
                        inputs(2) = mCoulNeg;
                        inputs(3) = mIntegralSampling;
                        inputs(4) = mrtype;
                        inputs(5) = mrsize;
                        inputs(6) = mrcutoff;
                        inputs(7) = mttype;
                        inputs(8) = mtsize;
                        inputs(9) = mttol;
                        inputs(10) = mExportMat;
                        inputs(11) = mPrintLevel;
                        inputs(12) = mocc;
                        inputs(13) = mvirt;
                        inputs(14) = mnmo;
                        inputs(15) = mnbsf;
                        inputs.save(folder+"inputs.vec", arma::arma_ascii);

                        mf_mat.save(folder+"f.mat", arma::arma_ascii);
                        mc_mat.save(folder+"c.mat", arma::arma_ascii);
                        mcgto_mat.save(folder+"cgto.mat", arma::arma_ascii);
                        mcoulomb.save(folder+"coulomb.cube", arma::arma_ascii);

                        mrgrid.get_mgpts().save(folder+"rpts.mat", arma::arma_ascii);
                        mrgrid.get_mgwts().save(folder+"rwts.mat", arma::arma_ascii);

                        mtgrid.get_mgpts().save(folder+"tpts.mat", arma::arma_ascii);
                        mtgrid.get_mgwts().save(folder+"twts.mat", arma::arma_ascii);
                }
        }//export_toFile

}//namespace libjove
