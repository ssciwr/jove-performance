#ifndef LIBJOVE_DO_MP2_TEST_H
#define LIBJOVE_DO_MP2_TEST_H

#include <string>

namespace libjove {

class do_mp2_test {
        public: 
                bool run_test(std::string folder, double cenergy, float tol);
};

}//namespace libjove

#endif //LIBJOVE_DO_MP2_TEST_H
