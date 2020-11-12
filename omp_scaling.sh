#!/usr/bin/env bash

# simple bash script to see OMP scaling with number of threads
# takes the Wall clock reported by Main Timer
# assumes the library has been built in /build

echo "# threads	wall clock (ms)"
cd build/tests
for n in 1 2 3 4 5 6 7 8 9 10 11 12
do
  t=$(OMP_NUM_THREADS=$n ./libjove_tests | grep "Main Timer" | awk '{print $9}')
  echo "$n		$t"
done
cd ../..
