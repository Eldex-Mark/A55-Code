#CMake file for different scenarios: Native build on Linux or Windows (automatic), and cross-build from Unix to Windows (by defining build-host as Unix and build-target as Windows)

cmake_minimum_required( VERSION 3.12 )

project( TestBench C )

#set(CMAKE_C_OUTPUT_EXTENSION .o)  #needed to produce objects with .o extension like the original well-working makefile did, so fsp.ld will find these for linking, especially secure code (so secure_code.bin won't be 0 sized)
#set(CMAKE_RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E rename <OBJECT>.c.o <OBJECT>.o")

if (NOT DEFINED SQUARELINE_BUILD_TARGET__UNIX)
    set( SQUARELINE_BUILD_TARGET__UNIX 0 )
endif()
if (NOT DEFINED SQUARELINE_BUILD_TARGET__WINDOWS)
    set( SQUARELINE_BUILD_TARGET__WINDOWS 0 )
endif()
if (NOT DEFINED SQUARELINE_BUILD_TARGET__BOARD)
    set( SQUARELINE_BUILD_TARGET__BOARD 0 )
endif()
if (NOT DEFINED SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)
    set( SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 0 )
endif()
if (NOT DEFINED SQUARELINE_BUILD_TARGET__BOARD__CORE_A55)
    set( SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 0 )
endif()
if (NOT DEFINED SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
    set( SQUARELINE_BUILD_TARGET__EMSCRIPTEN 0 )
endif()
if (NOT DEFINED SQUARELINE_DEBUG)
    set( SQUARELINE_DEBUG 0 )
endif()
add_definitions (
    -DSQUARELINE_BUILD_TARGET__UNIX=${SQUARELINE_BUILD_TARGET__UNIX}
    -DSQUARELINE_BUILD_TARGET__WINDOWS=${SQUARELINE_BUILD_TARGET__WINDOWS}
    -DSQUARELINE_BUILD_TARGET__BOARD=${SQUARELINE_BUILD_TARGET__BOARD}
    -DSQUARELINE_BUILD_TARGET__BOARD__CORE_M33=${SQUARELINE_BUILD_TARGET__BOARD__CORE_M33}
    -DSQUARELINE_BUILD_TARGET__BOARD__CORE_A55=${SQUARELINE_BUILD_TARGET__BOARD__CORE_A55}
    -DSQUARELINE_BUILD_TARGET__EMSCRIPTEN=${SQUARELINE_BUILD_TARGET__EMSCRIPTEN}
    -DSQUARELINE_DEBUG=${SQUARELINE_DEBUG}
)

set( BUILD_CASE__UNIX_NATIVE 0 )
set( BUILD_CASE__UNIX_TO_WINDOWS 0 )
set( BUILD_CASE__WINDOWS_NATIVE 0 )
set( BUILD_CASE__UNIX_TO_BOARD 0 )
if     ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (NOT SQUARELINE_BUILD_TARGET__WINDOWS) AND (NOT SQUARELINE_BUILD_TARGET__BOARD) AND (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) AND (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) AND (NOT SQUARELINE_BUILD_TARGET__EMSCRIPTEN) )  #AND (DEFINED SQUARELINE_BUILD_TARGET__UNIX) (VSCode wouldn't work with this)
    set( BUILD_CASE__UNIX_NATIVE 1 )
elseif ( (WIN32 OR (DEFINED SQUARELINE_BUILD_HOST__WINDOWS)) AND (NOT SQUARELINE_BUILD_TARGET__UNIX) AND (NOT SQUARELINE_BUILD_TARGET__BOARD) AND (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) AND (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) AND (NOT SQUARELINE_BUILD_TARGET__EMSCRIPTEN) )  #AND (DEFINED SQUARELINE_BUILD_TARGET__WINDOWS) (VSCode wouldn't work with this)
    set( BUILD_CASE__WINDOWS_NATIVE 1 )
elseif ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (SQUARELINE_BUILD_TARGET__WINDOWS) )
    set( BUILD_CASE__UNIX_TO_WINDOWS 1 )
elseif ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (SQUARELINE_BUILD_TARGET__BOARD) )
    set( BUILD_CASE__UNIX_TO_BOARD 1 )
elseif ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) )
    set( BUILD_CASE__UNIX_TO_BOARD__CORE_M33 1 )
elseif ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) )
    set( BUILD_CASE__UNIX_TO_BOARD__CORE_A55 1 )
elseif ( (UNIX OR (DEFINED SQUARELINE_BUILD_HOST__UNIX)) AND (SQUARELINE_BUILD_TARGET__EMSCRIPTEN) )
    set( BUILD_CASE__UNIX_TO_EMSCRIPTEN 1 )
endif()

set( CMAKE_C_STANDARD 11 )
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused -g" )
set( CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} )
#set( CMAKE_C_FLAGS -g ) #for callgrind
#set( CMAKE_C_FLAGS -pg ) #for gprof


include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/Modules/Common
    ${PROJECT_SOURCE_DIR}/Modules/Common/GUI_API
    ${PROJECT_SOURCE_DIR}/Modules/Common/CoreMessaging
    if (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_A55)
     ${PROJECT_SOURCE_DIR}/Modules/CoreM33/CoreMessaging
    endif()
    if (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)
     ${PROJECT_SOURCE_DIR}/Modules/CoreA55/CoreMessaging
     ${PROJECT_SOURCE_DIR}/Modules/CoreA55/GUI
    endif()
)


if ( (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) AND (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) )
 #set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=pointer-arith -Werror=int-conversion  -fstrict-aliasing -Werror=strict-aliasing -Wcast-align" )  #observe pointer type castings/conversions
 set( App_Sources TestBench.c CoreM33_Example.c CoreA55_Example.c )
 FILE( GLOB_RECURSE GUI_Sources CONFIGURE_DEPENDS Modules/Common/*.c Modules/CoreM33/CoreMessaging/*.c Modules/CoreA55/*.c )
endif()


if (BUILD_CASE__UNIX_TO_WINDOWS) #Unix to Windows cross-compilation

    set( CMAKE_SYSTEM_NAME Generic )

    set( CMAKE_CROSSCOMPILING true )
    set( CMAKE_SYSTEM_PROCESSOR x86_64 )
    set( CMAKE_LIBRARY_ARCHITECTURE x86_64-w64-mingw32 )
    set( CMAKE_C_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-gcc )
    set( CMAKE_CXX_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-g++ )
    set( CMAKE_LINKER ${CMAKE_LIBRARY_ARCHITECTURE}-ld )


elseif (BUILD_CASE__UNIX_TO_BOARD OR BUILD_CASE__UNIX_TO_BOARD__CORE_A55)

    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O" )

    if (BUILD_CASE__UNIX_TO_BOARD__CORE_A55)
     set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -g -DCFG_CA5X" )  #these were found in the Makefile of the MHU example
     set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-type-limits" )  #comparing unsigned with <= to an offset which might be 0, if it works like this in rzg2_rproc.c, might not be a problem
     set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-to-int-cast" )  #tests show integer will be able to hold a value castef from the pointer in rzg2_rproc.c, at least the code worked
     set ( MHU_FOLDER Modules/CoreA55/OpenAMP_MHU )
     include_directories ( ${MHU_FOLDER} )
     set( App_Sources CoreA55_Example.c )
     FILE( GLOB_RECURSE GUI_Sources CONFIGURE_DEPENDS Modules/Common/*.c Modules/CoreA55/*.c )
     FILE( GLOB_RECURSE MHU_Sources CONFIGURE_DEPENDS Modules/CoreA55/CoreMessaging/*.c Modules/CoreA55/OpenAMP_MHU/*.c )
    endif()

    set( CMAKE_SYSTEM_NAME Generic )

    set( CMAKE_CROSSCOMPILING true )
    set( CMAKE_SYSTEM_PROCESSOR aarch64 )
    set( CMAKE_LIBRARY_ARCHITECTURE aarch64-poky-linux )
    set( CMAKE_C_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-gcc )
    set( CMAKE_CXX_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-g++ )
    set( CMAKE_LINKER ${CMAKE_LIBRARY_ARCHITECTURE}-ld )


elseif (BUILD_CASE__UNIX_TO_BOARD__CORE_M33)


    set( EXECUTABLE_BASENAME ${PROJECT_NAME}-board-CoreM33 )
    set( EXECUTABLE_FILENAME ${EXECUTABLE_BASENAME}.elf )

    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb -mcmse -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wuninitialized -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -Wl,--start-group ${OBJS} ${USER_OBJS} -Wl,--end-group -T ${PROJECT_SOURCE_DIR}/Modules/CoreM33/Renesas_MHU/script/fsp.ld -lc -lgcc -lnosys -L${PROJECT_SOURCE_DIR}/Modules/CoreM33/Renesas_MHU/script -nostartfiles -Xlinker --gc-sections -Wl,-Map,${EXECUTABLE_BASENAME}.map --specs=nano.specs --specs=rdimon.specs --specs=nosys.specs" )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-old-style-declaration" ) #'static' is not before 'volatile' seems not a big issue
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-float-equal " )  #we take care about this by only comparing float-to-float and double-to-double in the code, so this warning is false here
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion -Wno-sign-compare -Wno-int-conversion -Wno-pointer-sign" )  #there are a lot of them in Renesas/FreeRTOS/libmetal code, better suppressing for now until any problems arise from this
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-missing-declarations -Wno-implicit-function-declaration" )  #these are really a problem, but suppressing it for now as the source builds fine with them
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-stringop-truncation" )  #this occurs many times but doesn't cause problem if string is not maximum-length, suppressing for now until any problems arise from this
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-arith -Wno-incompatible-pointer-types" )  #This is a problem, but suppressing it for now to not litter our own code's compilation error logs

    set ( MHU_FOLDER Modules/CoreM33/Renesas_MHU )
    set ( RZG_FOLDER ${MHU_FOLDER}/rzg )
    set ( FSP_FOLDER ${RZG_FOLDER}/fsp )
    include_directories (
        ${MHU_FOLDER}/src
        ${MHU_FOLDER}/rzg_cfg/aws  ${MHU_FOLDER}/rzg_cfg/fsp_cfg  ${MHU_FOLDER}/rzg_cfg/fsp_cfg/bsp    ${MHU_FOLDER}/rzg_gen
        ${RZG_FOLDER}/arm/CMSIS_5/CMSIS/Core/Include  ${RZG_FOLDER}/aws/amazon-freertos/freertos_kernel/include    ${RZG_FOLDER}/linaro/libmetal/include  ${RZG_FOLDER}/linaro/open-amp/lib/include
        ${FSP_FOLDER}/inc/api  ${FSP_FOLDER}/inc/instances    ${FSP_FOLDER}/src/bsp/mcu/rzg2l  ${FSP_FOLDER}/src/rm_freertos_port
    )

    #add_definitions(-DNO_TRUSTZONE_SECURITY)
    set( App_Sources CoreM33_Example.c )
    FILE( GLOB_RECURSE MHU_Sources CONFIGURE_DEPENDS Modules/Common/*.c Modules/CoreM33/CoreMessaging/*.c Modules/CoreM33/Renesas_MHU/*.c ) #${RZG_FOLDER}/board/rzg2l_smarc/*.c ${FSP_FOLDER}/src/bsp/mcu/all/*.c ${FSP_FOLDER}/src/bsp/cmsis/*.c )

    set( CMAKE_SYSTEM_NAME Generic )

    set( CMAKE_CROSSCOMPILING true )
    set( CMAKE_SYSTEM_PROCESSOR arm )
    set( CMAKE_LIBRARY_ARCHITECTURE arm-none-eabi )
    set( CMAKE_C_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-gcc )
    set( CMAKE_CXX_COMPILER ${CMAKE_LIBRARY_ARCHITECTURE}-g++ )
    set( CMAKE_LINKER ${CMAKE_LIBRARY_ARCHITECTURE}-ld )
    set( CMAKE_OBJCOPY ${CMAKE_LIBRARY_ARCHITECTURE}-objcopy )

    add_executable( ${EXECUTABLE_FILENAME} ${App_Sources} ${MHU_Sources} )
    target_link_libraries( ${EXECUTABLE_FILENAME} PRIVATE -lc -lgcc -lnosys )

    add_custom_command( TARGET ${EXECUTABLE_FILENAME} POST_BUILD
        COMMAND  ${CMAKE_OBJCOPY}  -O ihex  ${EXECUTABLE_FILENAME}  ${EXECUTABLE_BASENAME}.hex
        COMMAND  ${CMAKE_OBJCOPY}  -O binary  -j .secure_vector  ${EXECUTABLE_FILENAME}  ${EXECUTABLE_BASENAME}-secure_vector.bin
        COMMAND  ${CMAKE_OBJCOPY}  -O binary  -j .non_secure_vector  ${EXECUTABLE_FILENAME}  ${EXECUTABLE_BASENAME}-non_secure_vector.bin
        COMMAND  ${CMAKE_OBJCOPY}  -O binary  -j .secure_code  ${EXECUTABLE_FILENAME}  ${EXECUTABLE_BASENAME}-secure_code.bin
        COMMAND  ${CMAKE_OBJCOPY}  -O binary  -j .non_secure_code  -j .data  ${EXECUTABLE_FILENAME}  ${EXECUTABLE_BASENAME}-non_secure_code.bin
    )


elseif (BUILD_CASE__UNIX_TO_EMSCRIPTEN)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s USE_SDL=2  -Wno-unused-parameter -Wno-limited-postlink-optimizations" )  #suppress unused/unoptimized stuff's warnings

    set( LV_CONF_BUILD_DISABLE_EXAMPLES 1 )
    set( LV_CONF_BUILD_DISABLE_DEMOS 1 )

    add_subdirectory( Modules/CoreA55/GUI/lvgl )
    add_subdirectory( Modules/CoreA55/GUI/ui )

    set( SOURCES ${App_Sources} ${GUI_Sources} )


endif()

if (NOT SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)
    include( Modules/CoreA55/GUI/CMakeLists.txt )
endif()

