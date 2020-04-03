#!/usr/bin/env bash
#set -eo pipefail

if [[ "$DEBUG_CI" == true ]]; then
  set -x
fi

# Default configuration when used out of travis-ci
MODE=${MODE:-Debug}
EXTRA_CMAKE_OPTIONS=${EXTRA_CMAKE_OPTIONS:-}
BUILD_TEST=${BUILD_TEST:-true}

if [[ -n ${TRAVIS_BUILD_DIR:+x} ]]; then
echo
    cd ${TRAVIS_BUILD_DIR}
fi


echo $PATH
echo "-------------------------------------------"
#echo "FIND:"
#find "/c" -iname "cl.exe" || true
#find "/c" -iname "msbuild.exe" || true
#find "/c" -iname "devenv.exe" || true
#find "/c" -iname "cmake*" || true
find "/c" -iname "Common7" || true
echo "-------------------------------------------"
export PATH="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin/amd64":$PATH
export PATH="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin":$PATH
export PATH="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE":$PATH
echo "-------------------------------------------"
echo "WHERE:"
where cl.exe || true
where msbuild.exe || true
where devenv.exe || true

export VS160COMNTOOLS="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/Tools"
echo "VS160COMNTOOLS = $VS160COMNTOOLS"

echo $PWD
mkdir -p build
cd build
echo "----------- A -------------"
cmake --debug-output --trace \
  -DCMAKE_GENERATOR_PLATFORM=x64 \
  -G "Visual Studio 16 2019" \
  ..

#  -DCMAKE_GENERATOR_INSTANCE="C:/Program Files (x86)/Microsoft Visual Studio/2019/Community"

echo "----------- TEST -------------"
cmake --build . --target ALL_BUILD --config ${MODE}