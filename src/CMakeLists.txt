include_directories(${CMAKE_SOURCE_DIR}/include)
if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib/win)
elseif(APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/lib/mac)
endif()

# libmupdfrender
add_library(mupdfrender STATIC)
target_sources(mupdfrender PRIVATE 
    mupdf_render.c
    mupdf_render.h
)
target_link_libraries(mupdfrender PRIVATE mupdf freetype jbig2dec jpeg openjpeg z)

# libpagerender
add_library(pagerender STATIC)
target_sources(pagerender PRIVATE 
    page_render.c
    page_render.h
)
target_link_libraries(pagerender PRIVATE mupdfrender)

# libpdftrick-native_v...
set(ARTIFACT_NAME pdftrick-native_${CMAKE_PROJECT_VERSION})
add_library(${ARTIFACT_NAME} SHARED)
target_sources(${ARTIFACT_NAME} PRIVATE 
    org_gmdev_pdftrick_nativeutil_NativeLibCall.c
)
target_link_libraries(${ARTIFACT_NAME} PRIVATE pagerender)
set_target_properties(${ARTIFACT_NAME} PROPERTIES PUBLIC_HEADER org_gmdev_pdftrick_nativeutil_NativeLibCall.h)

install(TARGETS ${ARTIFACT_NAME}
    RUNTIME DESTINATION ${INSTALL_CURRENT_DIR}/bin
    LIBRARY DESTINATION ${INSTALL_CURRENT_DIR}/lib
    ARCHIVE DESTINATION ${INSTALL_CURRENT_DIR}/lib
    PUBLIC_HEADER DESTINATION ${INSTALL_CURRENT_DIR}/include)








