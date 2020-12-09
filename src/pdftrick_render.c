#include "page_render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_lock_file(char *img_path);
void delete_lock_file(char *file_look_path);
int get_page_number_digits(int page_number);

void render_thumbail(const char *pdf_file_path, const char *images_folder_path,
                     const int page_number, const int zoom,
                     const int rotation) {

    char *image_ = "image_";
    char *extension = ".png";

    // int digits = get_page_number_digits(page_number);

    char num[10];
    sprintf(num, "%d", page_number);

    char *image_path = malloc((strlen(images_folder_path) + strlen(image_) +
                               strlen(num) + strlen(extension) + 4) *
                              sizeof(char));

    sprintf(image_path, "%s%s%s%s", images_folder_path, image_, num, extension);

    char *lock_file = create_lock_file(image_path);
    render(pdf_file_path, zoom, rotation, image_path, page_number);
    delete_lock_file(lock_file);
    free(image_path);
}

int get_page_number_digits(int page_number) {
    int digits = 0;
    while (page_number != 0) {
        digits++;
        page_number /= 10;
    }
    return digits;
}

char *create_lock_file(char *image_path) {
    char *extension = ".look";
    char *lock_file_path =
        malloc((strlen(image_path) + strlen(extension) + 4) * sizeof(char));

    sprintf(lock_file_path, "%s%s", image_path, extension);

    FILE *lock_file = fopen(lock_file_path, "w");

    if (lock_file == NULL)
        return NULL;

    fclose(lock_file);
    return lock_file_path;
}

void delete_lock_file(char *lock_file_path) {
    remove(lock_file_path);
    free(lock_file_path);
}