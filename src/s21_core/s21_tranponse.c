#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = IsCorr(A);
  if (status == kOk) {
    status = s21_create_matrix(A->columns, A->rows, result) != kOk;
    for (int i = 0; status == kOk && i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return status;
}