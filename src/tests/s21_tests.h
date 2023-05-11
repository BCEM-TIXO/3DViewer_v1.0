#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

#include <check.h>

#include "../s21_core/s21_parser.h"

#define EPS 1e-7
Suite *suite_parser();
Suite *suite_transform();

#endif  // SRC_TESTS_S21_TESTS_H_
