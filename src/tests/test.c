#include "s21_tests.h"

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *runner;
  s = suite_parser();
  runner = srunner_create(s);

  srunner_add_suite(runner, suite_transform());
  // srunner_add_suite(runner, suite_arifmethic());
  // srunner_add_suite(runner, suite_transpose());
  // srunner_add_suite(runner, suite_determinant());
  // srunner_add_suite(runner, suite_calc_complements());
  // srunner_add_suite(runner, suite_inverse());

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}