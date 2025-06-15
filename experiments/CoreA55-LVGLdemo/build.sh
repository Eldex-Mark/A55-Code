#!/bin/sh

#All patches of https://github.com/renesas-rz/meta-rz-demo-lvgl are added to the original https://github.com/lvgl/lv_port_linux/tree/adf2c4490e17a1b9ec1902cc412a24b3b8235c8e , and -linput was added to Makefile

#Need to have the aarch64-poky-linux toolchain and x86_64-pokysdk-linux in /opt folder (available in SDK package of https://d.myirtech.com/MYD-YG2LX/

. /opt/poky/3.1.20/environment-setup-aarch64-poky-linux

#Need to have full LVGL source in 'lvgl' folder (built/tested with 8.3.11).

make clean
make UserDefined="-D LV_COLOR_DEPTH_BY_MAKE=32 -D USE_LIBINPUT=1 -D USE_EVDEV=0 -D USE_WAYLAND=0 -D LV_DEMO_MUSIC_LARGE=1" BIN=lvgldemo_32FP all
#make UserDefined="-D LV_COLOR_DEPTH_BY_MAKE=32 -D USE_LIBINPUT=0 -D USE_EVDEV=0 -D USE_FBDEV=0 -D USE_WAYLAND=1 -D LV_WAYLAND_WL_SHELL=1 -D LV_WAYLAND_XDG_SHELL=0 -D LV_WAYLAND_TIMER_HANDLER=1 -D LV_DEMO_MUSIC_LARGE=1" BIN=lvgldemo_32W all

#Then copy the generated executable to the Yocto CIP-linux of the board and run it (automatically in /etc/profile after 'pkill weston')
