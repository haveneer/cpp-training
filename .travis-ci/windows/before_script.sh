#!/usr/bin/env bash
set -eo pipefail

if [[ "$DEBUG_CI" == true ]]; then
  set -x
fi

if [[ "$DEBUG_CI" == true ]]; then
    echo $PATH
    cmake --version
fi

#cmake --version # 3.16.2
vswhere
vswhere -all -prerelease -property installationPath
echo "-------------------------------------------"
#cmake -G || true
#echo "PATH = $PATH"
#echo "-------------------------------------------"
#echo "VS160COMNTOOLS = $VS160COMNTOOLS"
#echo "-------------------------------------------"
#find -name "/c/"
