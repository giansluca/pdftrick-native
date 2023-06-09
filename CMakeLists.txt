cmake_minimum_required(VERSION 3.18)
project(c-utils VERSION 1.0.3 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(WIN32)
    MESSAGE(STATUS "Platform windows")
    add_compile_options(-m64 -Wall)
elseif(APPLE)
    MESSAGE(STATUS "Platform apple")
    add_compile_options(-m64 -Wall)
endif()

MESSAGE(STATUS "current project dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
MESSAGE(STATUS "current install dir: " ${INSTALL_CURRENT_DIR})

add_subdirectory(src)
add_subdirectory(test)

# unit tests
enable_testing()
add_test(NAME PdfTrick-native COMMAND run-tests)
list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")
