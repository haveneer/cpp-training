#!/usr/bin/env bash
set -eo pipefail

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

choco install visualstudio2019community
choco install visualstudio2019-workload-nativedesktop