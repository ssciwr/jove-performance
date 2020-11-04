#ifndef LIBJOVE_TTIMER_H
#define LIBJOVE_TTIMER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>

namespace libjove {
        /** \brief Timer objects
         * A class for creating timer objects and printing their values.
         *
         * \ingroup libjove
         **/
        class ttimer {
                private: 
                        std::clock_t mcpu_start;
                        std::clock_t mcpu_stop;

                        std::chrono::high_resolution_clock::time_point mwall_start;
                        std::chrono::high_resolution_clock::time_point mwall_stop;

                        bool mrun;
                        std::string mname;

                public: 
                        ttimer () : mname("Unnamed"), mrun (0) {};
                        ttimer (std::string name) : mname (name), mrun (0) {};
                        
                        void reset () {
                                mrun = 1;
                                mcpu_start = std::clock();
                                mwall_start = std::chrono::high_resolution_clock::now();
                        } //reset

                        void stop () {
                                if (mrun){
                                mrun = 0;
                                mcpu_stop = std::clock();
                                mwall_stop = std::chrono::high_resolution_clock::now();
                                }//if
                        } // stop

                        void start() {
                                if (!mrun) {
                                    mrun = 1;
                                    mcpu_start = std::clock();
                                    mwall_start = std::chrono::high_resolution_clock::now();
                                }
                        }//start
                        std::chrono::high_resolution_clock::duration wall_time () {
                                return mwall_stop - mwall_start;
                        }//wall

                        std::clock_t cpu_time () {
                                return mcpu_stop - mcpu_start;
                        }//cpu_time

                        void print (std::ostringstream &out) {
                                        out << std::fixed << std::setprecision(0) 
                                                << "  " << mname <<" Timer - "
                                                <<"CPU: "
                                        <<1000.0 * cpu_time() / CLOCKS_PER_SEC << " ms ; "
                                        << "Wall: "
                                        << std::chrono::duration_cast<std::chrono::milliseconds>(wall_time()).count() << " ms\n";
                        }//print
        }; //class ttimer

}//namespace libjove

#endif
