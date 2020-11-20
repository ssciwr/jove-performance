#include "../../libjove/vaults/vault_mp2.h"
#include "../../libjove/mp/do_mp2.h"
#include "../../libjove/loader/loader_mp2_fromfile.h"
#include "do_mp2_test.h"

#include <iostream>
#include <cmath>

namespace libjove {
        bool do_mp2_test::run_test (std::string folder, double cenergy, float tol){

                vault_mp2 vault;
                loader_mp2_fromfile loader;

                loader.perform(folder, vault);
                
                do_mp2 mp2;
                std::ostringstream out;
                double energy = 0;
                energy = mp2.calc_mp2(out, vault);

                return ((std::abs(energy - cenergy) <= tol) ? 1 : 0);        
        }//run_test

}//namespace libjove
