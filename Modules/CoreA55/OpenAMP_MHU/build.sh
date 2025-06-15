#!/bin/sh

#Need to have the aarch64-poky-linux toolchain and x86_64-pokysdk-linux in /opt folder (available in SDK package of https://d.myirtech.com/MYD-YG2LX/

. /opt/poky/3.1.20/environment-setup-aarch64-poky-linux

make

rm *.o

#Then copy the generated executable to the Yocto CPI-linux of the board and run it after the FreeRTOS code is running on the other core.
