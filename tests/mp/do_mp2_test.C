#include "../../libjove/vaults/vault_mp2.h"
#include "../../libjove/mp/do_mp2.h"
#include "../../libjove/loader/loader_mp2_fromfile.h"
#include "do_mp2_test.h"

#include <string>
#include <iostream>

namespace libjove {
        bool do_mp2_test::run_test (){
                std::string folder = "../../data/h2o";

                vault_mp2 vault;
                loader_mp2_fromfile loader;

                loader.perform("../../data/h2o/", vault);
                
                do_mp2 mp2;
                std::ostringstream out;
                double energy = 0;
                energy = mp2.calc_mp2(out, vault);
                std::cout << out.str() << std::endl;

                return (((energy + 0.12422) <= 0.0001) ? 1 : 0);        
        }//run_test

}//namespace libjove
