#ifndef LIBJOVE_LOADER_MP2_QCHEM_H
#define LIBJOVE_LOADER_MP2_QCHEM_H

#include <armadillo>
#include <sstream>
#include "../vaults/vault_mp2.h"
#include "../grid/jove_grid.h"

namespace libjove {
        /** \brief Interface class for the Q-MP2 method with Q-Chem
         * This prepares the data from qchem and saves it into an 
         * spezialized vault object. 
         *
         * \ingroup libjove
         *
         **/
        class loader_mp2_qchem {
                private: 

                public:
                        loader_mp2_qchem() {};

                        /** \brief Load the vault object
                         *
                         * \param[in] vault : reference to data storage class
                         *
                         **/ 
                        void perform (vault_mp2 &vault);
        };
}//NAMESPACE LIBJOVE

#endif //LIBJOVE_LOADER_QCHEM_H
