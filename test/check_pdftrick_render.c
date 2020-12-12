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
    char *page = "10";
    char *image_path = build_image_path(images_folder_path, page);

    ck_assert_str_eq(expected, image_path);

    free(image_path);
}
END_TEST

Suite *general_suite(void) {
    Suite *suite;
    TCase *pdftrick_render;

    suite = suite_create("General");
    pdftrick_render = tcase_create("pdftrick_render");

    tcase_add_test(pdftrick_render, it_should_calculate_digits_of_a_number);
    tcase_add_test(pdftrick_render, it_should_build_image_path);

    suite_add_tcase(suite, pdftrick_render);

    return suite;
}

int main(void) {
    int number_failed = 0;
    Suite *suite;
    SRunner *suite_runner;

    suite = general_suite();
    suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}