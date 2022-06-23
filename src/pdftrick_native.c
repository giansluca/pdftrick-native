#include "org_gmdev_pdftrick_nativeutil_NativeLibCall.h"
#include "pdftrick_render.h"

JNIEXPORT void JNICALL
Java_org_gmdev_pdftrick_nativeutil_NativeLibCall_renderThumbnail(
    JNIEnv *env, jobject obj, jstring _pdf_file_path,
    jstring _images_folder_path, jint _page_number, jint _zoom) {

    const char *pdf_file_path =
        (*env)->GetStringUTFChars(env, _pdf_file_path, 0);
    const char *images_folder_path =
        (*env)->GetStringUTFChars(env, _images_folder_path, 0);
    const int page_number = (int)_page_number;
    const int zoom = (int)_zoom;
    const int rotation = 0;

    render_thumbnail(pdf_file_path, images_folder_path, page_number, zoom,
                     rotation);

    (*env)->ReleaseStringUTFChars(env, _images_folder_path, images_folder_path);
    (*env)->ReleaseStringUTFChars(env, _pdf_file_path, pdf_file_path);
}

JNIEXPORT void JNICALL
Java_org_gmdev_pdftrick_nativeutil_NativeLibCall_renderFull(
    JNIEnv *env, jobject obj, jstring _pdf_file_path,
    jstring _images_folder_path, jint _page_number, jint _zoom) {

    const char *pdf_file_path =
        (*env)->GetStringUTFChars(env, _pdf_file_path, 0);
    const char *images_folder_path =
        (*env)->GetStringUTFChars(env, _images_folder_path, 0);

    // TODO
    // const int page_number = (int)_page_number;
    // const int zoom = (int)_zoom;
    // const int rotation = 0;

    (*env)->ReleaseStringUTFChars(env, _images_folder_path, images_folder_path);
    (*env)->ReleaseStringUTFChars(env, _pdf_file_path, pdf_file_path);
}
