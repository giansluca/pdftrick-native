#include "org_gmdev_pdftrick_nativeutil_NativeLibCall.h"
#include "page_render.h"
#include <mupdf/fitz.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render(const char *, int, int, char *, int);
char *createLookFile(char *img_path);
void deleteLookFile(char *file_look_path);

JNIEXPORT void JNICALL Java_org_gmdev_pdftrick_nativeutil_NativeLibCall_start(
    JNIEnv *env, jobject obj, jstring resultfile, jstring path, jint nPage,
    jint zoom) {

    const char *string_resultfile =
        (*env)->GetStringUTFChars(env, resultfile, 0);
    const char *string_path = (*env)->GetStringUTFChars(env, path, 0);

    int numberPage = (int)nPage;
    int zoomPic = (int)zoom;
    int rotation = 0;

    char *image_ = "image_";
    char *extension = ".png";

    char num[10];
    sprintf(num, "%d", numberPage);
    char *img_path = (char *)malloc((strlen(string_path) + strlen(image_) +
                                     strlen(num) + strlen(extension) + 4) *
                                    sizeof(char));

    sprintf(img_path, "%s%s%s%s", string_path, image_, num, extension);

    char *look_file = createLookFile(img_path);
    render(string_resultfile, zoomPic, rotation, img_path, numberPage);
    deleteLookFile(look_file);
    free(img_path);

    (*env)->ReleaseStringUTFChars(env, path, string_path);
    (*env)->ReleaseStringUTFChars(env, resultfile, string_resultfile);
}

JNIEXPORT void JNICALL Java_org_gmdev_pdftrick_nativeutil_NativeLibCall_cover(
    JNIEnv *env, jobject obj, jstring resultfile, jstring path, jint nPage,
    jint zoom) {

    const char *string_resultfile =
        (*env)->GetStringUTFChars(env, resultfile, 0);
    const char *string_path = (*env)->GetStringUTFChars(env, path, 0);

    int numberPage = (int)nPage;
    int zoomPic = (int)zoom;
    int rotation = 0;

    char *name_file = "cover_page_";
    char *extension = ".png";

    char num[10];
    sprintf(num, "%d", numberPage);

    char *img_path = (char *)malloc((strlen(string_path) + strlen(name_file) +
                                     strlen(num) + strlen(extension) + 4) *
                                    sizeof(char));

    sprintf(img_path, "%s%s%s%s", string_path, name_file, num, extension);
    render(string_resultfile, zoomPic, rotation, img_path, numberPage);
    free(img_path);

    (*env)->ReleaseStringUTFChars(env, path, string_path);
    (*env)->ReleaseStringUTFChars(env, resultfile, string_resultfile);
}

char *createLookFile(char *img_path) {
    char *look = ".look";
    char *file_look_path =
        (char *)malloc((strlen(img_path) + strlen(look) + 4) * sizeof(char));

    sprintf(file_look_path, "%s%s", img_path, look);

    FILE *f = fopen(file_look_path, "w");

    if (f == NULL)
        return NULL;

    fclose(f);
    return file_look_path;
}

void deleteLookFile(char *file_look_path) {
    remove(file_look_path);
    free(file_look_path);
}
