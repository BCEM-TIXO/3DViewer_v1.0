#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = IsSim(A, B);
  if (status != kOk) {
    return kNotEq;
  }
  status = kEq;
  for (int i = 0; status == kEq && i < A->rows; i++) {
    for (int j = 0; status == kEq && j < A->columns; j++) {
      if (fabsf(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
        status = kNotEq;
      }
    }
  }
  return status;
}