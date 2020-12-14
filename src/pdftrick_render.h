#ifndef PDFTRICK_NATIVE_PDFTRICK_RENDER_H
#define PDFTRICK_NATIVE_PDFTRICK_RENDER_H

void render_thumbail(const char *pdf_file_path, const char *images_folder_path,
                     const int page_number, const int zoom, const int rotation);

char *build_image_path(const char *images_folder_path, int page_number);
int get_page_number_digits(int page_number);

#endif