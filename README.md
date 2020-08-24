[![C++ CI](https://github.com/haveneer/cpp-training/workflows/C++%20CI/badge.svg)](https://github.com/haveneer/cpp-training/actions) [![Build Status](https://travis-ci.com/haveneer/cpp-training.svg?branch=master)](https://travis-ci.com/haveneer/cpp-training)

All this material is dedicated to a C++ training given by [me](https://www.haveneer.com).

For more details about this training, contact me [hpwxf@haveneer.com](mailto:hpwxf@haveneer.com).

# cpp-training

* Any file `filename.cpp` is automatically compiled using extra files `filename.h*` `filename--*.*`

* Any file `filename--unittest.cpp` is a google test and is automatically compiled using extra files `filename.h*` `filename--*.*`

* Any file `filaname.cxx` is not compiled and usually contains explicit bugs 

* `type.h` contains tool `type(obj)` to get printable type name for given object argument 

# CMake options

* `-DENABLE_STATIC_ANALYSIS=ON|OFF` : enable/disable static analysis while compiling
 
* `-DCMAKE_CXX_COMPILER_LAUNCHER=ccache` : enable `ccache` as compiler cache
