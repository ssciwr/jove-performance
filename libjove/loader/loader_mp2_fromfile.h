#ifndef LIBJOVE_LOADER_MP2_FROMFILE_H
#define LIBJOVE_LOADER_MP2_FROMFILE_H

#include <armadillo>
#include <string>

#include "../vaults/vault_mp2.h"

namespace libjove {
        /** \brief Setup the data storage object from files
         * This handles the setup of the needed data from files. 
         *
         * \ingroup libjove
         *
         **/
        class loader_mp2_fromfile {
                private: 

                public:
                        loader_mp2_fromfile() {};

                        /** \brief Load the vault object
                         *
                         * \param[in] vault : reference to data storage class
                         *
                         **/ 
                        void perform (std::string folder, vault_mp2 &vault);
        };
}//NAMESPACE LIBJOVE

#endif //LIBJOVE_LOADER_MP2_FROMFILE_H
