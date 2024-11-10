#!/bin/sh
# Cross-build in Linux for the board

. /opt/poky/3.1.20/environment-setup-aarch64-poky-linux

rm  -r  build
mkdir  -p  build
cd build

cmake  ..  --no-warn-unused-cli  -DSQUARELINE_BUILD_HOST__UNIX=1  -DSQUARELINE_BUILD_TARGET__BOARD__CORE_A55=1  -DCMAKE_BUILD_TYPE=Debug #Release
make  -j2

cd ..


