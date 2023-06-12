cmake_minimum_required(VERSION 3.18)
project(c-utils VERSION 1.0.3 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(WIN32)
    message(STATUS "Platform windows")
    add_compile_options(-m64 -Wall)
elseif(APPLE)
    message(STATUS "Platform apple")
    add_compile_options(-m64 -Wall)
endif()

message(STATUS "current project dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)

# unit tests
enable_testing()
add_test(NAME PdfTrick-native COMMAND run-tests)
list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")
