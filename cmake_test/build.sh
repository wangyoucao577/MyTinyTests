#!/bin/bash

BUILD_FOLDER="./build"

if [ $# -ge 1 ]; then
    if [ $1 = "clean" ]; then
        rm -rf ${BUILD_FOLDER}
        exit 0
    fi
fi


if [ ! -d ${BUILD_FOLDER} ]; then
    mkdir ${BUILD_FOLDER}
fi

cd ${BUILD_FOLDER}
cmake ..
make
cd ..



