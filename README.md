[![C++ CI](https://github.com/haveneer/cpp-training/workflows/C++%20CI/badge.svg)](https://github.com/haveneer/cpp-training/actions) [![Build Status](https://travis-ci.com/haveneer/cpp-training.svg?branch=master)](https://travis-ci.com/haveneer/cpp-training)

<p xmlns:dct="http://purl.org/dc/terms/" xmlns:cc="http://creativecommons.org/ns#" class="license-text">
    <a rel="cc:attributionURL" property="dct:title" href="https://github.com/haveneer/cpp-training">
        Code snippets for C++ training
    </a>
    by 
    <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="mailto:hpwxf@haveneer.com">
        Pascal HAVÉ
    </a> is licensed under 
    <a rel="license" href="https://creativecommons.org/licenses/by-nc-sa/4.0">CC BY-NC-SA 4.0
        <img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" /><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" /><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1" /><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" />
    </a>
</p>

For more details about this training, contact me [hpwxf@haveneer.com](mailto:hpwxf@haveneer.com).

# cpp-training

* Any file `filename.cpp` is automatically compiled using extra files `filename.h*` `filename--*.*`

* Any file `filename--unittest.cpp` is a google test and is automatically compiled using extra files `filename.h*` `filename--*.*`

* Any file `filaname.cxx` is not compiled and usually contains explicit bugs 

* `type.h` contains tool `type(obj)` to get printable type name for given object argument 

# CMake options

* `-DENABLE_STATIC_ANALYSIS=ON|OFF` : enable/disable static analysis while compiling
 
* `-DCMAKE_CXX_COMPILER_LAUNCHER=ccache` : enable `ccache` as compiler cache


