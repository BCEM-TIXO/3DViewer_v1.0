#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = kOk;
  if (result == NULL || rows <= 0 || columns <= 0) {
    return kMatrIncorrect;
  }
  float *tmp = (float *)malloc(rows * columns * sizeof(float));
  result->matrix = (float **)malloc(rows * sizeof(float *));
  if (result->matrix == NULL) {
    status = kMatrIncorrect;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = tmp + i * columns;
  }
  result->columns = columns;
  result->rows = rows;

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (IsCorr(A) == kOk) {
    free(A->matrix[0]);
  }
  free(A->matrix);
  A->columns = 0;
  A->rows = 0;
  A->matrix = NULL;
}