#include "../src/page_render.h"
#include "common.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

START_TEST(it_should_calculate_digits_of_a_number) {
    ck_assert_int_eq(get_page_number_digits(1), 1);
    ck_assert_int_eq(get_page_number_digits(10), 2);
    ck_assert_int_eq(get_page_number_digits(100), 3);
    ck_assert_int_eq(get_page_number_digits(1000), 4);
    ck_assert_int_eq(get_page_number_digits(10000), 5);
}
END_TEST

START_TEST(it_should_build_image_path) {
    char *expected = "test_path/image_10.png";

    char *images_folder_path = "test_path/";
    int page_number = 10;
    char *image_path = build_image_path(images_folder_path, page_number);

    ck_assert_str_eq(expected, image_path);

    free(image_path);
}
END_TEST

START_TEST(it_should_create_lock_file) {
    make_dir("test/resources");

    char *image_path = "test/resources/file.png";
    char *lock_file_path = create_lock_file(image_path);

    ck_assert_int_eq(access(lock_file_path, F_OK), 0);

    char file_string[10];
    FILE *fp = fopen(lock_file_path, "r");
    fscanf(fp, "%s", file_string);

    ck_assert_int_eq(strcmp(file_string, "Created"), 0);

    fclose(fp);
    remove(lock_file_path);
    free(lock_file_path);
}
END_TEST

START_TEST(it_should_render_thumbnail) {
    make_dir("test/out-files");

    char *pdf_file_path = "../../test/resources/basic-1.pdf";
    char *images_folder_path = "test/out-files/";
    int page_number = 99;
    int zoom = 30;
    int rotation = 0;

    render_thumbnail(pdf_file_path, images_folder_path, page_number, zoom,
                     rotation);

    char *expected_image_path = "test/out-files/image_99.png";
    ck_assert_int_eq(access(expected_image_path, F_OK), 0);

    remove(expected_image_path);
}
END_TEST

Suite *page_render_suite(void) {
    Suite *suite;
    TCase *tcase;

    suite = suite_create("Page render suite");
    tcase = tcase_create("Page render test case");

    tcase_add_test(tcase, it_should_calculate_digits_of_a_number);
    tcase_add_test(tcase, it_should_build_image_path);
    tcase_add_test(tcase, it_should_create_lock_file);
    tcase_add_test(tcase, it_should_render_thumbnail);

    suite_add_tcase(suite, tcase);

    return suite;
}
