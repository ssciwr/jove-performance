# libjove

Working GIT of the JOVE (high-performance parallelization of QC calculations through grid quadrature) Project at the Dreuw Group
This library should be stand-alone if armadillo is installed. Use the do_configure script to set up your cmake environment. 

TODOs:
- implement omni-grid class 
- implement simple 3d grid for visualization (?)
- new parallelization scheme
- HPC ready

## Benchmark history

The serial speed-up from each commit to the repo:

- [0](https://github.com/ssciwr/jove-performance/commit/301456c5f643a935abef0628a5edc8eb1f8b1b35): original version
- [1](https://github.com/ssciwr/jove-performance/commit/f87ef27788cc33d5cceb1764b3526e7d9919e983): transpose data storage order to be more cache friendly
- [2](https://github.com/ssciwr/jove-performance/commit/e3bf8948cf872f88556be4e5facfc130fad8fad1): swap loop order to traverse data in cache friendly way
- [3](https://github.com/ssciwr/jove-performance/commit/b12d8e45c3533d69f2f02c5e2ecd924eab1299d4): do half the work by exploiting `p <-> q` symmetry
- [4](https://github.com/ssciwr/jove-performance/commit/eb5d88e977ab9e25f9d67640c25690c57575029a): use [Eigen](https://eigen.tuxfamily.org) instead of Armadillo to generate vectorized code
- [5](https://github.com/ssciwr/jove-performance/commit/6e44a30dc6f18f9f8faf02e99e7f9b7d8c874eb1): refactor to avoid some copies
- [6](https://github.com/ssciwr/jove-performance/commit/90b66ba36773a49b1464b5c6d166ace945ab2735): avoid hidden copies in armadillo

See the relevant commit message & changes to the code for more details

![benchmark](benchmark.png)

The parallel speed-up from each commit to the repo:

- [tsize](https://github.com/ssciwr/jove-performance/commit/ad5555cd3a866fe4f5891a0213fce31b440d477b): parallelize over `tsize`
- [npts](https://github.com/ssciwr/jove-performance/commit/6f09110046bd1ca68a2d736ab77a65e66d59357a): parallelize over `npts`
- [tsize+npts](https://github.com/ssciwr/jove-performance/commit/b6d5a45df752d4a317542e6828c8cc402c46087f): parallelize over `tsize` and `npts`
- [tsize+npts/dynamic](https://github.com/ssciwr/jove-performance/commit/06722f4918bee199c391a76d138a35924cf05af7): parallelize over `tsize` and `npts` + dynamic scheduling
- [tsize+npts/dynamic/OMP_PROC_BIND](https://github.com/ssciwr/jove-performance/commit/57348b411257e3b8bbdd95faff600337e1e64566): parallelize over `tsize` and `npts` + dynamic scheduling + `export OMP_PROC_BIND=true` to stop OS from moving threads between cores

See the relevant commit message & changes to the code for more details

![scaling](scaling.png)
