#ifndef LIBJOVE_PPRINTER_H 
#define LIBJOVE_PRINTER_H

#include <iostream>
#include "../vaults/vault_mp2.h"

namespace libjove{
        /** \brief Printer class for libjove
         * This class handles the printing of the resulting data 
         * to the output stream. 
         *
         * \ingroup libjove
         **/
        class pprinter 
            {
                    public: 
                            /** \brief Prepares the printing output
                             **/
                            void prep_print (std::ostringstream &out);
                            /** \brief Prints the MP2 specific input and output
                             **/
                            void print_mp2 (vault_mp2 &vault, std::ostringstream &out);
            }; //class pprinter

}//namespace libjove

#endif
