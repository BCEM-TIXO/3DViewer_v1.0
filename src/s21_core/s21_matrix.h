#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_struct {
  float **matrix;
  int rows;
  int columns;
} matrix_t;

enum matrix_status { kOk, kMatrIncorrect, kMatrCacl, kNotEq = 0, kEq };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int IsCorr(matrix_t *A);

int IsQuad(matrix_t *A);

int IsSim(matrix_t *A, matrix_t *B);

int IsMul(matrix_t *A, matrix_t *B);

void enter_matrix_float(matrix_t *A, float *mat);

#include <stdio.h>

void print_matrix(matrix_t *A);

#endif
