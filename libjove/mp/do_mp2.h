#ifndef LIBJOVE_DO_MP2_H
#define LIBJOVE_DO_MP2_H

#include <iostream>
#include <armadillo>
#include "../vaults/vault_mp2.h"

namespace libjove{

        class do_mp2 {

                /** \brief Class that handles the calculation of the Q-MP2  method
                 *
                 * This class is used for the handling of the Q-MP2 method.
                 * The run method is called from the host program. 
                 *
                 * \ingroup libjove
                 *
                 **/
                public: 
                        do_mp2() {};

                        /** \brief Start the Q-MP2 calculation
                         * This method is called from the host program. 
                         *
                         * \param[in] out : output stream
                         * \param[in] vault : data holding object
                         **/

                        void run (std::ostringstream &out, vault_mp2 &vault); 

                        /** \brief Internally Q-MP2 calculation, returns energy
                         * This internally method hosts the calculation of the MP2 energy
                         * and returns it. 
                         *
                         * \param[in] oss : output stream
                         * \param[in] vault : data holding object
                         **/ 
                        double calc_mp2 (std::ostringstream &oss, 
                                vault_mp2 &vault);
                private: 
        };


} //namespace libjove

#endif //LIBJOVE_DO_MP2
