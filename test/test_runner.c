#include "test_headers.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int number_failed = 0;
    Suite *_functions_suite = functions_suite();
    Suite *_render_suite = render_suite();

    SRunner *srunner = srunner_create(_functions_suite);
    srunner_add_suite(srunner, _render_suite);

    srunner_run_all(srunner, CK_NORMAL);
    number_failed = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}