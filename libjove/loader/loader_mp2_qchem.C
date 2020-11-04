#include "loader_mp2_qchem.h"
#include "../integrals/jove_vmul.h"
#include "../grid/jove_grid.h"

#include <armadillo>

#include <qchem.h>

#include <libqints/basis/basis_1e1c_cgto.h>
#include <libqints/qchem/aobasis.h>
#include <libqints/types.h>
#include <libqints/ftype/ftype_cgto.h>

#include <libgrid/libgrid/eval_cgto.h>

namespace libjove {
    void loader_mp2_qchem::perform (vault_mp2 &vault){
        libqints::basis_1e1c_cgto<double> basis = libqints::qchem::aobasis.b1;

        bool Scale = (rem_read(REM_JOVE_SCALE) == 1) ? 1 : 0; 
        bool Transform = (rem_read(REM_JOVE_TRANSFORM) == 1) ? 1 : 0;
        bool CoulNeg = (rem_read(REM_JOVE_COUL_NEG) == 1) ? 1 : 0;
        bool IntegralSampling = (rem_read(REM_JOVE_INTEGRAL_SAMPLING) == 1) ? 1 : 0;
        size_t rtype = (rem_read(REM_JOVE_RTYPE) > 0) ? rem_read(REM_JOVE_RTYPE) : 1 ;
        size_t rsize = (rem_read(REM_JOVE_RSIZE) > 0) ? rem_read(REM_JOVE_RSIZE) : 0;
        bool rcutoff = (rem_read(REM_JOVE_RCUTOFF) > 0) ? 1 : 0;
        size_t ttype = (rem_read(REM_JOVE_TTYPE) > 0) ? rem_read(REM_JOVE_TTYPE) : 1;
        size_t tsize = ((rem_read(REM_JOVE_TSIZE)>=1)&&
                        (rem_read(REM_JOVE_TSIZE)<=1024)) ? rem_read(REM_JOVE_TSIZE) : 4; 
        double ttol = ((rem_read(REM_JOVE_TTOL)<14)&&
                        (rem_read(REM_JOVE_TTOL)>=8)) ? pow((double)10.0, 
                                (double) -1*rem_read(REM_JOVE_TTOL)) : 1e-10; 
        bool ExportMat = (rem_read(REM_JOVE_EXPORT_MAT) == 1) ? 1 : 0;
        size_t PrintLevel = (rem_read(REM_JOVE_PRINT_LEVEL) > 0 ) ? rem_read(REM_JOVE_PRINT_LEVEL) : 0;
        size_t occ = rem_read(REM_NALPHA);
        size_t nmo = rem_read(REM_NLINOR);
        size_t virt = nmo - occ;
        size_t nbsf = basis.get_nbsf();

        //CREATE F_MAT AND C_MAT
        arma::mat f_mat(nbsf,nbsf, arma::fill::zeros);
        arma::mat c_mat(nbsf, nmo, arma::fill::zeros);
        FileMan(FM_READ, FILE_FOCK_MATRIX, FM_DP, f_mat.n_elem, 0, FM_BEG, f_mat.memptr()); 
        FileMan(FM_READ, FILE_MO_COEFS, FM_DP, c_mat.n_elem, 0, FM_BEG, c_mat.memptr());
        
        //CREATE GRIDS
        jove_grid tgrid;
        tgrid.init_grid(ttype, tsize, 0, 1, ttol);
        jove_grid rgrid;
        rgrid.init_grid(rtype);
        int npts = rgrid.get_gridSize();

        
        //CREATE CGTO_MAT
        arma::mat cgto_mat(npts, nbsf, arma::fill::zeros);
        arma::mat mrpts=rgrid.get_mgpts();
        int error = libgrid::eval_cgto(basis, mrpts, cgto_mat);

        //CREATE COULOMB
        std::vector< libqints::ftype_multipole > v_pts;

        for (int i = 0; i < npts; i++){
            libqints::ftype_multipole f_mult;
            f_mult.x = mrpts(0,i);
            f_mult.y = mrpts(1,i);
            f_mult.z = mrpts(2,i);
            f_mult.k = 0;
            v_pts.push_back(f_mult);
        }//for i
        
        libqints::basis_1e1c_multipole bm (v_pts);

        double mom[npts];
        for (int i = 0; i < npts; i++) mom[i] = 1;

        libqints::array_view<double> av_mom((double*) &mom[0], npts);
         
        libqints::dev_omp dev;
        arma::cube coulomb(nbsf, nbsf, npts);
        libqints::array_view<double> av_vmul(coulomb.memptr(), npts*nbsf*nbsf);
        dev.init(256UL * 1024*1024);
        jove_vmul<double>(basis, bm, dev).compute(av_mom, av_vmul);
        
        vault.load (Scale, Transform, CoulNeg, IntegralSampling, rtype,
                rsize, rcutoff, ttype, tsize, ttol, ExportMat, 
                PrintLevel, occ, virt, nmo, nbsf, f_mat, c_mat, cgto_mat,
                coulomb, rgrid, tgrid);

    }//perform
}//namespace libjove
