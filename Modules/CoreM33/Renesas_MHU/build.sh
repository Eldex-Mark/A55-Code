#!/bin/sh

#Should have arm-none-eabi gcc-toolchain installed on the system to build this for the 32bit CM33 core

cd build

make clean
make
find . -name '*.o' -type f -delete
find . -name '*.o.in' -type f -delete

cd ../script
./postbuild.sh

#After building copy the .bin files to the board and load+run them at startup in uboot manually or 'bootcmd' as described in the multi-os PDF.

#Important: For CMake-based build the .o extensions in scripts/fsp.ld linker-script were modified to .c.o which CMake generates whatever is set.

