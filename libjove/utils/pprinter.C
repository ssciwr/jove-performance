#include "pprinter.h"

namespace libjove {

        void pprinter::prep_print (std::ostringstream &out){
                out<<"--------------------------------------------------------------------------------"<<std::endl;
                out<<"                                MP2 using JOVE                                  "<<std::endl;
                out<<"--------------------------------------------------------------------------------"<<std::endl;
        }//prep_print

        void pprinter::print_mp2 (vault_mp2 &vault, std::ostringstream &out){
                if (vault.get_mPrintLevel() > 0) {
                        out<<"--------------------------------------------------------------------------------"<<std::endl;
                        out<<"                              JOVE Printout Requested                           "<<std::endl;
                        out<<"--------------------------------------------------------------------------------"<<std::endl;
                        out<<"--------------------------------- Job Information ------------------------------"<<std::endl;
                        (vault.get_mScale()) ? out<<"  Enabled" : out<<"  Disabled";
                        out<<" MO-Energy Scaling to facilitate integration."<<std::endl;
                        (vault.get_mExportMat()) ? out<<"  Enabled" : out<<"  Disabled";
                        out<<" export matrices used during JOVE."<<std::endl;
                        out<<"------------------------------- System Information -----------------------------"<<std::endl;
                        out<<"  Number of basis functions: "<<vault.get_mnbsf()<<std::endl;
                        out<<"  Number of MOs: "<<vault.get_mnmo()<<std::endl;
                        out<<"  Number of Occupied MOs: "<<vault.get_mocc()<<std::endl;
                        out<<"  Number of Virtual MOs: "<<vault.get_mvirt()<<std::endl;
                        out<<"------------------------------- r-Grid Information -----------------------------"<<std::endl;
                        if (vault.get_mrtype()==1) out<<"  Spacial Grid employed. MoleGrid of libdftn used for r-Grid creation."<<std::endl;
                        else out<<"  Unknown grid used for r-Grid creation."<<std::endl;
                        out<<"  Number of Points in r grid: "<<vault.get_mrsize()<<std::endl;
                        out<<"------------------------------- t-Grid Information -----------------------------"<<std::endl;
                        if (vault.get_mttype()==1) out<<"  Gauss-Legendre quadrature employed. External Lib by Pavel Holoborodko used."<<std::endl;
                        else out<<"  Unknown grid used for t-Grid creation."<<std::endl;
                        out<<"  Number of Points in t grid: "<<vault.get_mtsize()<<std::endl;
                        out<<"  Requested Tolerance of t grid: "<<vault.get_mttol()<<std::endl;
                        out<<"--------------------------------------------------------------------------------"<<std::endl;
                }//if  
        }//print_mp2
}//namespace libjove
