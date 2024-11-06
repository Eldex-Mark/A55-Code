rem Build on native Windows with GCC of MinGW

rd  build  /S  /Q
md  build
cd  build

cmake  -G "MinGW Makefiles"  ..  --no-warn-unused-cli  -DSQUARELINE_BUILD_HOST__WINDOWS=1  -DSQUARELINE_BUILD_TARGET__WINDOWS=1  -DCMAKE_BUILD_TYPE=Debug
mingw32-make  -j2

cd  ..

copy  SDL2.dll  build
md  build\GUI
md  build\GUI\assets
xcopy  Modules\CoreA55\GUI\assets  build\GUI\assets  /s /e /h

run.bat

