#ifndef SRC_TR_M_H_
#define SRC_TR_M_H_

#include "s21_obj.h"

int init_matr(matrix_t *A);

int init_move_matr(matrix_t *A, float x, float y, float z);

void move_xyz(obj_t *obj, float x, float y, float z);
void rotate_xyz(obj_t *obj, float angle_x, float angle_y, float angle_z);
void scale_xyz(obj_t *obj, float x, float y, float z);
void normalize(obj_t *obj);
#endif
