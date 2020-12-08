#include "../src/pdftrick_render.h"
#include <stdio.h>

int main(int argn, char **argv) {
    printf("START TESTS\n");

    char *pdf_file_path = "../../test/resources/basic-1.pdf";
    char *images_folder_path = "../../test/resources/";
    int page_number = 10;
    int zoom = 30;
    int rotation = 0;

    render_thumbail(pdf_file_path, images_folder_path, page_number, zoom,
                    rotation);

    printf("END TESTS\n");
    return 0;
}