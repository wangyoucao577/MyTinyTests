#!/bin/bash

CMAKE_GENERATED_CONFIG="cmake_config.h"
BUILD_FOLDER="./build"

if [ $# -ge 1 ]; then
    if [ $1 = "clean" ]; then
        rm -rf ${BUILD_FOLDER}
        rm -f ${CMAKE_GENERATED_CONFIG}
        exit 0
    fi
fi


if [ ! -d ${BUILD_FOLDER} ]; then
    mkdir ${BUILD_FOLDER}
fi

cd ${BUILD_FOLDER}
cmake -DCMAKE_CONFIG_FILE=${CMAKE_GENERATED_CONFIG} ..
make
cd ..



