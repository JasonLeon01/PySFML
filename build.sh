#!/bin/bash

set -e

if [ ! -d "build" ]; then
    mkdir build
else
    find build -mindepth 1 -not -name '_deps' -exec rm -rf {} +
fi

cd build

cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_BUILD_TYPE=Release .. --trace-expand
cmake --build .
