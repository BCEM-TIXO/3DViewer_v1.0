#ifndef SRC_S21_OBJ_H_
#define SRC_S21_OBJ_H_

#include "s21_matrix.h"

typedef struct obj_struct {
  int vertexs_count;
  matrix_t vertexs;
  unsigned *faces;
  int faces_lenght;
  int faces_count;
  // float xyz_max[3];
  // float max;
  float offset[3];
} obj_t;

int init_obj(obj_t *obj);

void remove_obj(obj_t *obj);

#endif
