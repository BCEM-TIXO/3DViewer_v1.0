#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = IsMul(A, B);
  if (status == kOk && s21_create_matrix(A->rows, B->columns, result) != kOk) {
    status = kMatrIncorrect;
  }
  for (int i = 0; status == kOk && i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return status;
}