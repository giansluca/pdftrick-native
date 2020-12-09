#include "../src/pdftrick_render.h"
#include <stdio.h>

void render_integration_test(int page_number) {
    printf("START TESTS\n");

    char *pdf_file_path = "../../test/resources/basic-1.pdf";
    char *images_folder_path = "../../test/out-files/";
    int zoom = 30;
    int rotation = 0;

    render_thumbail(pdf_file_path, images_folder_path, page_number, zoom,
                    rotation);

    printf("END TESTS\n");
}

int main(void) {
    render_integration_test(10);
    return 0;
}
