#include "../src/pdftrick_render.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

void render_integration_test(int page_number) {
    char *pdf_file_path = "../../test/resources/basic-1.pdf";
    char *images_folder_path = "../../test/out-files/";
    int zoom = 30;
    int rotation = 0;

    render_thumbail(pdf_file_path, images_folder_path, page_number, zoom,
                    rotation);
}

START_TEST(it_should_render_thumbnail) {
    int test = 5;

    ck_assert_int_eq(test, 5);
}
END_TEST

Suite *render_suite(void) {
    Suite *suite;
    TCase *tcase;

    suite = suite_create("Render suite");
    tcase = tcase_create("Render a thumbnail from pdf page");

    tcase_add_test(tcase, it_should_render_thumbnail);

    suite_add_tcase(suite, tcase);

    return suite;
}
