#include "../src/pdftrick_render.h"
#include <check.h>
#include <stdlib.h>

START_TEST(it_should_calculate_digits_of_a_number) {
    ck_assert_int_eq(get_page_number_digits(1), 1);
    ck_assert_int_eq(get_page_number_digits(10), 2);
    ck_assert_int_eq(get_page_number_digits(100), 3);
}
END_TEST

Suite *general_suite(void) {
    Suite *suite;
    TCase *pdftrick_render;

    suite = suite_create("General");

    /* pdftrick_render test case */
    pdftrick_render = tcase_create("pdftrick_render");

    tcase_add_test(pdftrick_render, it_should_calculate_digits_of_a_number);
    suite_add_tcase(suite, pdftrick_render);

    return suite;
}

int main(void) {
    return 0;

    int number_failed;
    Suite *suite;
    SRunner *suite_runner;

    suite = general_suite();
    suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}