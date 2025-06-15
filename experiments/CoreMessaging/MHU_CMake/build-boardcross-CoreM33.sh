#!/bin/sh
# Cross-build in Linux for the board's M33 core

#Should have arm-none-eabi gcc-toolchain installed on the system to build this for the 32bit CM33 core

rm  -r  build
mkdir  -p  build
cd build

cmake  ..  --no-warn-unused-cli  -DSQUARELINE_BUILD_HOST__UNIX=1  -DSQUARELINE_BUILD_TARGET__BOARD__CORE_M33=1  -DCMAKE_BUILD_TYPE=Debug  #-DNO_TRUSTZONE_SECURITY=1
make  -j2

#post-build is done by CMake
#filebody=TestBench-board-CoreM33
#inputfilename=${filebody}.elf
#arm-none-eabi-objcopy -O binary -j .secure_vector ${inputfilename} ${filebody}_secure_vector.bin
#arm-none-eabi-objcopy -O binary -j .non_secure_vector ${inputfilename} ${filebody}_non_secure_vector.bin
#arm-none-eabi-objcopy -O binary -j .secure_code ${inputfilename} ${filebody}_secure_code.bin
#arm-none-eabi-objcopy -O binary -j .non_secure_code -j .data ${inputfilename} ${filebody}_non_secure_code.bin

cd ..

#After building copy the .bin files to the board and load+run them at startup in uboot manually or 'bootcmd' as described in the multi-os PDF.
