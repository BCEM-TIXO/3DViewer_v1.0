#include "s21_tests.h"

START_TEST(test1) {
  obj_t cube;
  matrix_t A;
  s21_create_matrix(8, 4, &A);
  float expect[] = {
                    0.0, 0.0, 0.0, 1.0, 
                    0.0, 0.0, 1.0, 1.0,
                    0.0, 1.0, 0.0, 1.0,
                    0.0, 1.0, 1.0, 1.0,
                    1.0, 0.0, 0.0, 1.0,
                    1.0, 0.0, 1.0, 1.0,
                    1.0, 1.0, 0.0, 1.0,
                    1.0, 1.0, 1.0, 1.0
                    };
  enter_matrix_float(&A, expect);
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  ck_assert_int_eq(cube.vertexs_count, 8);
  ck_assert_int_eq(cube.faces_count, 12);
  ck_assert_int_eq(s21_eq_matrix(&A, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  remove_obj(&cube);
}
END_TEST

START_TEST(test2) {
  obj_t cube;
  ck_assert_int_eq(parser("abracadabra", &cube), kOpenFileErr);
  remove_obj(&cube);
}
END_TEST

START_TEST(test3) {
  obj_t cube;
  ck_assert_int_eq(parser("./objs/file_without_v.obj", &cube), kFileIncorrect);
  remove_obj(&cube);
}
END_TEST

START_TEST(test4) {
  obj_t cube;
  ck_assert_int_eq(parser("./objs/file_without_f.obj", &cube), kFileIncorrect);
  remove_obj(&cube);
}
END_TEST

START_TEST(test5) {
  obj_t cube;
  ck_assert_int_eq(parser("./objs/file_with_neg_f.obj", &cube), kFileIncorrect);
  remove_obj(&cube);
}
END_TEST

START_TEST(test6) {
  obj_t cube;
  ck_assert_int_eq(parser("./objs/file_without_f_len.obj", &cube), kFileIncorrect);
  remove_obj(&cube);
}
END_TEST

Suite *suite_parser(void) {
  Suite *s = suite_create("suite_parser");
  TCase *tc = tcase_create("parser_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);

  suite_add_tcase(s, tc);

  return s;
}