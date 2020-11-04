#ifndef LIBJOVE_JOVE_H
#define LIBJOVE_JOVE_H

#include <armadillo>
#include <sstream>

#include "grid/jove_grid.h"
#include "utils/pprinter.h"
#include "utils/ttimer.h"
#include "mp/do_mp2.h"
#include "vaults/vault_mp2.h"

namespace libjove {

        /** \brief Planned Main class to run Quad-QC calculations
            
            This class is planned to be the main class to be called for the calculation of 
            quadrature adapted QC integrals. Right now it has no function but to include all 
            headers, as the Q-MP2 directive is to be called directly.
            
            \ingroup libjove
         **/
        class jove {
                private: 

                public:
                        jove() {}; //!< standard constructor
                        double do_mp2 (arma::mat &rpts, arma::mat &tpts, std::ostringstream &ostr); //!< planned method for calling the Q-MP2 method
                        void test (std::ostringstream &ostr); //!< test method
        };
}//NAMESPACE LIBJOVE

#endif //LIBJOVE_JOVE_H
