include_directories(${CMAKE_SOURCE_DIR}/include)
if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib/win)
elseif(APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/lib/mac)
endif()

set(ARTIFACT_NAME pdftrick-native_${CMAKE_PROJECT_VERSION})
add_library(${ARTIFACT_NAME} SHARED)
target_sources(${ARTIFACT_NAME} PRIVATE 
    org_gmdev_pdftrick_nativeutil_NativeLibCall.c
    org_gmdev_pdftrick_nativeutil_NativeLibCall.h
    page_render.c
    page_render.h
    mupdf_render.c
    mupdf_render.h
)

target_link_libraries(${ARTIFACT_NAME} PRIVATE freetype jbig2dec jpeg mupdf openjpeg z)









