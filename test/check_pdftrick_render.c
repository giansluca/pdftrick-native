#include "../src/pdftrick_render.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

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

Suite *functions_suite(void) {
    Suite *suite;
    TCase *tcase;

    suite = suite_create("Functions suite");
    tcase = tcase_create("Build image path string");

    tcase_add_test(tcase, it_should_calculate_digits_of_a_number);
    tcase_add_test(tcase, it_should_build_image_path);

    suite_add_tcase(suite, tcase);

    return suite;
}
