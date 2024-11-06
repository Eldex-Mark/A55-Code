

Later we'll give more detailed information, but in a nutshell about the usage of our GUI software-package for Eldex Optos Touch projec presented here:

The most important folder is the `Modules` folder where you can find all the program-sources and assets. The other folders are for building and testing reasons, or just to give you an example about the usage.

Inside the `Modules` there is the `Common` folder containing the code that is needed for both the compilation of the progam for A55 an M33 cores:
 - the API (at the current variable-names I gave)
 - and the inter-processor communication code in `CoreMessaging` folder.

In the `CoreA55` and `CoreM33` folder you can find the code for these specific cores.
 - For the A55 core the `GUI` folder has our essential GUI-code for your board. You'll need to include `GUI.h` as you see in the example testbench-sources in the main folder, and you'l need to provide `GUI_API.h` to us. (This can be renamed later if you have one already with another preferred name.)
 - For the M33 core the 'CoreMessaging' and Renesas folders are prepared for inter-CPU communication code.

At the moment only the main logic of the inter-processor communication is made, so it is only tried yet in simulation: we have both the M33 test-code and the A55 test-code compiled and running in the same instance.
( But variables are updated by the pseudo M33-core code to test how the interCPU messaging protocol is behaving in the simulation, so far so good.)

You can try out these pre-compiled executables, there are Windows, Linux executables as well es the one ending with `-board` which can be run on the Renesas devboard.
(The others are the sparated core-specific versions but they don't fully work due the incomplete low-level part of the inter-CPU communication. We'll priorize for this if you want to test the actual inter-Core communication asap.)

The easiest-to-run pre-compiled version is the 'TestBench.html' emscripten-built version, runnable from any browsers, and the necessary `GUI/assets` folder is embedded to it, you won't have any problem with paths/etc.


Building the project happens on linux with CMake on our side, the CMakeLists.txt file can handle various hosts and targets.
A made the convenience build-scripts starting with `build` that invokes cmake with the right defines to build for the different test-platforms and the board  (`build-boardcross.sh` is the one for the board).

We use the command-line poky linux SDK and standard GCC for compiling, you can see some comments about the toolchains in the respective build-scripts too.


2024 October SquareLine Team

