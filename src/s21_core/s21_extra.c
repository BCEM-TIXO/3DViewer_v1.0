#include "s21_matrix.h"

int IsCorr(matrix_t *A) {
  if (A != NULL && A->matrix && A->rows > 0 && A->columns > 0)
    return kOk;
  else
    return kMatrIncorrect;
}

int IsSim(matrix_t *A, matrix_t *B) {
  int status = IsCorr(A) || IsCorr(B);
  if (status == kOk && !(A->rows == B->rows && A->columns == B->columns))
    status = kMatrCacl;
  return status;
}

int IsMul(matrix_t *A, matrix_t *B) {
  int status = IsCorr(A) || IsCorr(B);
  if (status == kOk && A->columns != B->rows) status = kMatrCacl;
  return status;
}

void enter_matrix_float(matrix_t *A, float *mat) {
  memcpy(A->matrix[0], mat, A->columns * A->rows * sizeof(float));
}

/*
void print_matrix(matrix_t *A) {
  int col = A->columns;
  if (col > 10)
    col = 10;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < col; j++) {
        // printf("%d %d\n", i, j);
        printf("%.3f ", A->matrix[i][j]);
      }
      printf("%c", '\n');
    }
    printf("%c", '\n');
}
*/
