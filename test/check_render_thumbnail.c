#include "../src/pdftrick_render.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

START_TEST(it_should_render_thumbnail) {
    char *pdf_file_path = "test/resources/basic-1.pdf";
    char *images_folder_path = "test/out-files/";
    int page_number = 99;
    int zoom = 30;
    int rotation = 0;

    render_thumbail(pdf_file_path, images_folder_path, page_number, zoom,
                    rotation);

    char *expected_image_path = "test/out-files/image_99.png";
    ck_assert_int_eq(access(expected_image_path, F_OK), 0);

    remove(expected_image_path);
}
END_TEST

Suite *render_suite(void) {
    Suite *suite;
    TCase *tcase;

    suite = suite_create("Render suite");
    tcase = tcase_create("Render test case");

    tcase_add_test(tcase, it_should_render_thumbnail);

    suite_add_tcase(suite, tcase);

    return suite;
}
