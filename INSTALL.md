## Prerequisites

We recommend to install and run DSP on a **Linux** machine with an appropriate **MPI** library. The software packages necessary to build the source code of DSP are listed below.

*NOTE: We have also tested DSP on MacOSX (10.9 or later). This requires the user to install the required packages using Macports. We are currently developing documentation for this; please send us an e-mail if you have any questions.*

### Build essentials

You can install the build essential packages by using the shell script get.essentials in the DSP project repository or by manually installing the packages.

#### Using ./get.essentials script to install the build essential packages

You can run the apt-get commands to install the packages required for DSP by
```bash
sudo ./get.essentials
```
#### Manual installation of the build essential packages

If you have used ./get.essentials, then you can ignore this section and directly go to [External software packages](#External). Before using apt-get, please update the package list by typing
```bash
sudo apt-get update
```
* CMake -- This package is **required** to build DSP and all the other external software packages. It is available from http://www.cmake.org/download/. On Linux, you can also do
```bash
    sudo apt-get install cmake
```
* BLAS/LAPACK -- These linear algebra libraries are **required** and may already be available on your machine. If not available, the source codes are available from http://www.netlib.org/blas/blas.tgz and http://www.netlib.org/lapack/lapack-3.5.0.tgz. Or on linux you can install them by typing
```bash
    sudo apt-get install libblas-dev
    sudo apt-get install liblapack-dev
```
* svn -- A subversion software package is **required** to download an external package Coin-SMI used in DSP. You can install it by
```bash
    sudo apt-get install subversion
```
* GNU Make/Autoconf/Automake -- These are **required** and likely available on any machine. If not available, you can get them as follows.
```bash
    sudo apt-get install build-essential
    sudo apt-get install autoconf
    sudo apt-get install automake
```
* bzip2/zlib/xtuils-dev -- These packages are **required** to build one of the external software packages used in DSP.
```bash
    sudo apt-get install libbz2-dev
    sudo apt-get install zlib1g-dev
    sudo apt-get install xutils-dev
```
* MPICH -- A version of MPICH is **optional** to build and run DSP, but **required** to run DSP in parallel. This is available from http://www.mpich.org/downloads/. On Linux, you can also do
```bash
    sudo apt-get install libmpich-dev
```

<a name="External"></a>
### External software packages

The following packages are also **required** to build and run DSP and need to be located on ./extra directory before DSP may be built. **DSP will automatically configure and build the external packages once they are located in the right place.**

* MA27 (./extra/ma27-1.0.0) -- MA27 is a library for solving sparse symmetric indefinite linear systems. To build OOQP solver, you must have this installed. This is part of HSL (formerly the Harwell Subroutine Library), a collection of ISO Fortran codes for large scale scientific computation.
  1. Download: http://www.hsl.rl.ac.uk/download/MA27/1.0.0/a/
  2. Unpack the downloaded file.
  3. Move and rename the downloaded directory to ./extras/ma27-1.0.0/

* SCIP Optimization Suite (./extra/scipoptsuite-3.1.1) -- SCIP contains non-commercial solvers for mixed integer programming (MIP) and mixed-integer nonlinear programming (MINLP).
  1. Download: http://scip.zib.de/download.php?fname=scipoptsuite-3.1.1.tgz
  2. Unpack the downloaded file.
  3. Move and rename the downloaded directory to ./extras/scipoptsuite-3.1.1

## Installation

If you have all the prerequisite packages installed on your system, then you need to go to the root directory of DSP and type
```bash
mkdir build
cd build
cmake ..
```
to configure OOQP. If you wish to install the package in a more permanent location, you may then type
```bash
make install
```
External packages (MA27, OOQP, SCIP Optimization Suite, Smi) used in DSP are built automatically. A shared object is installed in ./lib directory. Once the installation has been successfully done, you need to set environment variable (DY)LD_LIBRARY_PATH.
Please add the following line by replacing \<DSP_SRC_PATH\> with your DSP source directory in ~/.bash_profile (or ~/.bash_aliases): for Linux,
```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<DSP_SRC_PATH>/lib
```
for Mac,
```bash
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:<DSP_SRC_PATH>/lib
```

## Test

You can run test problems using Julia scripts. Assuming that you are at ``<DSP_SRC_PATH>``, you can run the Julia test script for serial solvers,
```bash
julia test/test.jl
```
For parallel,
```bash
mpirun -n 4 julia test/test_mpi.jl
```