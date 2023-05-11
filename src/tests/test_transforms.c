#include "s21_tests.h"

START_TEST(test1) {
  obj_t cube;
  matrix_t A, B, Atr, C, Ctr;
  s21_create_matrix(8, 4, &A);
  s21_create_matrix(4, 4, &B);
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  float b[] = {
                1.0, 0.0, 0.0, 1.0, 
                0.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                0.0, 0.0, 0.0, 1.0,
                };
  
  enter_matrix_float(&A, a);
  enter_matrix_float(&B, b);
  s21_transpose(&A, &Atr);
  if (s21_mult_matrix(&B, &Atr, &C) == kOk) {
    s21_transpose(&C, &Ctr);
  }
  
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  move_xyz(&cube, 1, 1, 1);
  ck_assert_int_eq(s21_eq_matrix(&Ctr, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Atr);
  s21_remove_matrix(&Ctr);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  remove_obj(&cube);
}
END_TEST

START_TEST(test2) {
  obj_t cube;
  matrix_t A, B, Atr, C, Ctr;
  s21_create_matrix(8, 4, &A);
  s21_create_matrix(4, 4, &B);
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  float b[] = {
                2.0, 0.0, 0.0, 0.0, 
                0.0, 2.0, 0.0, 0.0,
                0.0, 0.0, 2.0, 0.0,
                0.0, 0.0, 0.0, 1.0,
                };
  
  enter_matrix_float(&A, a);
  enter_matrix_float(&B, b);
  s21_transpose(&A, &Atr);
if (s21_mult_matrix(&B, &Atr, &C) == kOk) {
    s21_transpose(&C, &Ctr);
  }
  
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  scale_xyz(&cube, 2, 2, 2);
  ck_assert_int_eq(s21_eq_matrix(&Ctr, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Atr);
  s21_remove_matrix(&Ctr);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  remove_obj(&cube);
}
END_TEST

START_TEST(test3) {
  obj_t cube;
  matrix_t A, B, Atr, C, Ctr;
  s21_create_matrix(8, 4, &A);
  s21_create_matrix(4, 4, &B);
  float angle = 30 * 0.01745329251;
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  float b[] = {
                1.0, 0.0, 0.0, 0.0, 
                0.0, cosf(angle), -sinf(angle), 0.0,
                0.0, sinf(angle), cosf(angle), 0.0,
                0.0, 0.0, 0.0, 1.0,
                };
  
  enter_matrix_float(&A, a);
  enter_matrix_float(&B, b);
  s21_transpose(&A, &Atr);
  if (s21_mult_matrix(&B, &Atr, &C) == kOk) {
    s21_transpose(&C, &Ctr);
  }
  
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  rotate_xyz(&cube, 30, 0, 0);
  ck_assert_int_eq(s21_eq_matrix(&Ctr, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Atr);
  s21_remove_matrix(&Ctr);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  remove_obj(&cube);
}
END_TEST

START_TEST(test4) {
  obj_t cube;
  matrix_t A, B, Atr, C, Ctr;
  s21_create_matrix(8, 4, &A);
  s21_create_matrix(4, 4, &B);
  float angle = 30 * 0.01745329251;
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  float b[] = {
                cosf(angle), 0.0, sinf(angle), 0.0, 
                0.0, 1.0, 0.0, 0.0,
                -sinf(angle), 0.0, cosf(angle), 0.0,
                0.0, 0.0, 0.0, 1.0,
                };
  
  enter_matrix_float(&A, a);
  enter_matrix_float(&B, b);
  s21_transpose(&A, &Atr);
  if (s21_mult_matrix(&B, &Atr, &C) == kOk) {
    s21_transpose(&C, &Ctr);
  }
  
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  rotate_xyz(&cube, 0, 30, 0);
  ck_assert_int_eq(s21_eq_matrix(&Ctr, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Atr);
  s21_remove_matrix(&Ctr);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  remove_obj(&cube);
}
END_TEST

START_TEST(test5) {
  obj_t cube;
  matrix_t A, B, Atr, C, Ctr;
  s21_create_matrix(8, 4, &A);
  s21_create_matrix(4, 4, &B);
  float angle = 30 * 0.01745329251;
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  float b[] = {
                cosf(angle), -sinf(angle), 0.0, 0.0, 
                sinf(angle), cosf(angle), 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0,
                };
  
  enter_matrix_float(&A, a);
  enter_matrix_float(&B, b);
  s21_transpose(&A, &Atr);
  if (s21_mult_matrix(&B, &Atr, &C) == kOk) {
    s21_transpose(&C, &Ctr);
  }
  
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  rotate_xyz(&cube, 0, 0, 30);
  ck_assert_int_eq(s21_eq_matrix(&Ctr, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  s21_remove_matrix(&Atr);
  s21_remove_matrix(&Ctr);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  remove_obj(&cube);
}
END_TEST

START_TEST(test6) {
  obj_t cube, t;
  matrix_t A;
  s21_create_matrix(8, 4, &A);
  float a[] = {
                0.0, 0.0, 0.0, 1.0, 
                0.0, 0.0, 1.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0
              };
  
  enter_matrix_float(&A, a);
  t.vertexs = A;
  scale_xyz(&t, 1/sqrtf(3), 1/sqrtf(3), 1/sqrtf(3));
  ck_assert_int_eq(parser("./objs/cube.obj", &cube), kOk);
  normalize(&cube);
  ck_assert_int_eq(s21_eq_matrix(&A, &cube.vertexs), kEq);
  s21_remove_matrix(&A);
  remove_obj(&cube);
}
END_TEST

Suite *suite_transform(void) {
  Suite *s = suite_create("suite_transform");
  TCase *tc = tcase_create("transform_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);

  suite_add_tcase(s, tc);

  return s;
}