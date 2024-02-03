# stonks

## homepage

See [Homepage](https://alkut.github.io/stonks/)

## requirements

- cmake 3.27+
- g++20 or higher
- (optional) doxygen, graphviz for generate documentation

## build

`git clone https://github.com/alkut/stonks` <br>
`cd stonks` <br>
`mkdir build` <br>
`cmake -S . -B ./build` <br>
(note: see cmake/Options.cmake) <br>
`cmake --build ./build -j {nproc}` <br>

## test

`cd ./build && ctest` <br>

## install

`git clone https://github.com/alkut/stonks` <br>
`cd stonks` <br>
`mkdir build` <br>
`cmake -DSTONKS_ENABLE_INSTALL=ON -S . -B ./build` <br>
`cmake --build ./build -j {nproc}` <br>
`cmake --install` <br>

Once library installed on the host machine, it is available by `find_package(Stonks)`.
That command propagate following cmake vars:

- Stonks_VERSION - version of library
- Stonks_INCLUDE_DIR - location of library include
  See examples/CmakeLists.txt for more information.

## generate docs

`git clone https://github.com/alkut/stonks` <br>
`cd stonks` <br>
`mkdir build` <br>
`cmake -DSTONKS_ENABLE_DOCS=ON -S . -B ./build` <br>
`cmake --build ./build --target docs -j {nproc}` <br>

doxygen, graphviz required. Artifacts can be found in docs/ folder

## benchmark

`git clone https://github.com/alkut/stonks` <br>
`cd stonks` <br>
`mkdir build` <br>
`cmake -DCMAKE_BUILD_TYPE=Release -DSTONKS_ENABLE_STONKS_ENABLE_BENCHMARKS=ON -S . -B ./build` <br>
`cmake --build ./build --target benchmark_tests -j {nproc}` <br>

## configuration

You can customize library configuration, see src/defines.h