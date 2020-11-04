#include <iostream>

#include "mp/do_mp2_test.h"

using namespace libjove;
using namespace std;

int main (){
        do_mp2_test mp2_test;
        cout << "Performing tests for libjove"<<endl;
        cout << "Testing do_mp2 ... "<<((mp2_test.run_test()) ? "passed" : "failed")<<endl;
        cout << "Tests done. Exiting."<<endl;
}
