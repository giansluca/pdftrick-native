find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)
if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib/win)
elseif(APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/lib/mac)
endif()

# build executable
add_executable(run-tests)
target_sources(run-tests PRIVATE 
    test_runner.c
    common.c
    common.h
    check_page_render.c
)

target_link_libraries(run-tests PRIVATE
    pdftrick-native_${CMAKE_PROJECT_VERSION}
    ${CHECK_LIBRARIES} 
)

