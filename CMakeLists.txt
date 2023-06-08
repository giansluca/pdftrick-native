cmake_minimum_required(VERSION 3.18)
project(c-utils VERSION 1.0.3 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(WIN32)
    MESSAGE(STATUS "Platform windows")
    if (MSVC)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        add_compile_options(/W4)
    else()
        add_compile_options(-m64 -Wall)
    endif()
elseif(APPLE)
    MESSAGE(STATUS "Platform apple")
    add_compile_options(-m64 -Wall)
endif()

MESSAGE(STATUS "current project dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
MESSAGE(STATUS "current install dir: " ${INSTALL_CURRENT_DIR})

add_subdirectory(src)
#add_subdirectory(test)

# unit tests
enable_testing()
add_test(NAME C-utils COMMAND run-tests)
list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")


# Example --> commands from project root
#
# -Debug-
# create makefile :         (mac)       cmake -S . -B build/debug -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -Wno-dev
#                           (debian)    cmake -S . -B build/debug -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -Wno-dev
#                           (windows)   cmake -G "Unix Makefiles" -S . -B build/debug -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -Wno-dev
# build :                   cmake --build build/debug
# run tests :               make test -C build/debug (ctest --test-dir build/debug -V)
# build and run tests :     make all test -C build/debug
# install:                  cmake --install build/debug
# clean :                   cmake --build build/debug --target clean
# run configuration :       cmake build/debug       

#
# -Release-
# create makefile :         (mac)       cmake -S . -B build/release -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release -Wno-dev
#                           (debian)    cmake -S . -B build/release -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -Wno-dev
#                           (windows)   cmake -G "Unix Makefiles" -S . -B build/debug -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -Wno-dev
# build :                   cmake --build build/release
# run tests :               make test -C build/release (ctest --test-dir build/release -V)
# build and run tests :     make all test -C build/release
# install:                  cmake --install build/release
# clean :                   cmake --build build/release --target clean
# run configuration :       cmake build/release

# Check library
# Mac :                     brew install check
# Windows (mysys) :         pacman -S mingw-w64-x86_64-check
#	                        pacman -S mingw-w64-i686-check
# Linux (debian) :          sudo apt install check




