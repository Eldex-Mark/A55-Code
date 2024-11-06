#!/bin/sh

rm  -r  build
mkdir  -p  build

mkdir  -p  build/GUI/assets
cp  -r  GUI/assets/*  build/GUI/assets

cd build

emcmake cmake  ..  -DSQUARELINE_BUILD_HOST__UNIX=1  -DSQUARELINE_BUILD_TARGET__EMSCRIPTEN=1  -DCMAKE_BUILD_TYPE=Release
emmake make  -j2

cd ..

./run-emscripten.sh

