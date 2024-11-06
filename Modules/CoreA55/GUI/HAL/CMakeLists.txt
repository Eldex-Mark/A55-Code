#Using external (outside of this source-code) SDL library, tipycally well detected on Linux

if (BUILD_CASE__UNIX_NATIVE) #Linux or MacOS host native compilation

    find_package( SDL2 REQUIRED SDL2 )

    include_directories ( ${SDL2_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}/../ )

    add_executable( ${PROJECT_NAME} ${App_Sources} ${GUI_Sources} )

    #string( STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES )

    target_link_libraries( ${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} )


elseif (BUILD_CASE__WINDOWS_NATIVE OR BUILD_CASE__UNIX_TO_WINDOWS)

    set( CMAKE_GENERATOR "MinGW Makefiles" )

    set( SDL_FOLDER Modules/CoreA55/GUI/HAL/sdl2-dev-x86_64 )
    set( CMAKE_FIND_ROOT_PATH ${SDL_FOLDER} )
    set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
    set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
    set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

    set( CMAKE_BUILD_RPATH "${SDL_FOLDER}/include" )
    set( CMAKE_INSTALL_RPATH ${CMAKE_BUILD_RPATH} )

    include_directories( ${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/include )

    FILE( GLOB_RECURSE SDL_Sources CONFIGURE_DEPENDS ${SDL_FOLDER} )

    add_executable( ${PROJECT_NAME} ${App_Sources} ${SDL_Sources} ${GUI_Sources} )

    add_custom_command (
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/SDL2.dll
            ${CMAKE_BINARY_DIR}/SDL2.dll
        COMMENT "Copying SDL2.dll to the build directory"
    )

    target_link_libraries( ${PROJECT_NAME} -L"${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/lib" SDL2 )


elseif (BUILD_CASE__UNIX_TO_BOARD)

    add_executable( ${PROJECT_NAME}-board ${App_Sources} ${GUI_Sources} )

    target_link_libraries( ${PROJECT_NAME}-board PRIVATE -linput -pthread )


elseif (BUILD_CASE__UNIX_TO_BOARD__CORE_A55)

    add_executable( ${PROJECT_NAME}-board-CoreA55 ${App_Sources} ${GUI_Sources} )

    target_link_libraries( ${PROJECT_NAME}-board-CoreA55 PRIVATE -linput -pthread )


elseif (BUILD_CASE__UNIX_TO_EMSCRIPTEN)

    add_executable( ${PROJECT_NAME} ${SOURCES} ${INCLUDES} )
    set( CMAKE_EXECUTABLE_SUFFIX ".html" )

    target_link_libraries( ${PROJECT_NAME} lvgl ui )

    set_target_properties( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "--shell-file ${PROJECT_SOURCE_DIR}/lvgl_shell.html -s SINGLE_FILE=1  --embed-file GUI/assets" )


endif()

