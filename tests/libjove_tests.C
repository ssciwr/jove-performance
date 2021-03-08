#include <iostream>

#include "mp/do_mp2_test.h"

using namespace libjove;
using namespace std;

int main (){
        do_mp2_test mp2_test;
        cout << "Performing tests for libjove" << endl;
        // cout << "Testing do_mp2 (H2O case) ... " << flush << ((mp2_test.run_test("../data/h2o_mp2/", -0.12422, 0.0001)) ? "passed" : "failed") << endl;
        cout << "Testing do_mp2 (H3COH case) ... " << flush << ((mp2_test.run_test("../data/h3coh_mp2/", -0.21635, 0.0001)) ? "passed" : "failed") << endl;
        // cout << "Testing do_mp2 (C14H10 case) ... " << flush << ((mp2_test.run_test("../data/c14h10_mp2/", -1.24223, 0.0001)) ? "passed" : "failed") << endl;
 
        cout << "Tests done. Exiting." << endl;
}
