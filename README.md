# HIBPM - Handling Inconsistencies in Business Process Modelling
Prototype for removing inconsistency in declare model via remainders.

Git submodules are used for libraries.
To download the submodules either clone using ``git clone --recurse-submodules <url>`` or after ``git clone`` use ``git submodule init`` and ``git submodule update``.

---

## Dependencies:
Following libraries are required to build the project.

**System Installation Required:**
- BISON version: 3.7.6
- FLEX version: 2.6.4

**Submodule:**
- [EvalMaxSAT](https://github.com/FlorentAvellaneda/EvalMaxSAT)

---

## Building

To build the project: 
```bash
cd <...>/hibpm
mkdir build && cd build
cmake ..
make -j<X> # X is the number of jobs/thread that you want to give the compiler to be quicker 
```

It could be that some compilers; e.g. `AppleClang 12.0.5.x` fail on trying to build `EvalMaxSAT`.
In this case, `g++` was tested and works with this setup.
To switch the compiler for building use:
```
cmake -DCMAKE_CXX_COMPILER=g++ ..
```
instead of the first line above.

On MasOS it might be, that you have to call the explicit version of `g++` by `g++-<version>` because Apple redirect `g++` back to `AppleClang`.
```
cmake -DCMAKE_CXX_COMPILER=g++-10 ..
```

