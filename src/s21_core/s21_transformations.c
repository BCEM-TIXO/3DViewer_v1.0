#include "s21_transformations.h"

void move_x(matrix_t *A, float x) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] += x;
  }
}

void move_y(matrix_t *A, float y) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][1] += y;
  }
}

void move_z(matrix_t *A, float z) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][2] += z;
  }
}

void move_to_zero(obj_t *obj) {
  move_x(&obj->vertexs, -obj->offset[0]);
  move_y(&obj->vertexs, -obj->offset[1]);
  move_z(&obj->vertexs, -obj->offset[2]);
}

void move_to_back(obj_t *obj) {
  move_x(&obj->vertexs, obj->offset[0]);
  move_y(&obj->vertexs, obj->offset[1]);
  move_z(&obj->vertexs, obj->offset[2]);
}

void move_xyz(obj_t *obj, float x, float y, float z) {
  obj->offset[0] += x;
  obj->offset[1] += y;
  obj->offset[2] += z;
  move_x(&obj->vertexs, x);
  move_y(&obj->vertexs, y);
  move_z(&obj->vertexs, z);
}

void rotate_x(matrix_t *A, float angle) {
  float cosf = cos(angle);
  float sinf = sin(angle);
  float y, z;
  for (int i = 0; i < A->rows; i++) {
    y = A->matrix[i][1];
    z = A->matrix[i][2];
    A->matrix[i][1] = cosf * y - sinf * z;
    A->matrix[i][2] = sinf * y + cosf * z;
  }
}

void rotate_y(matrix_t *A, float angle) {
  float cosf = cos(angle);
  float sinf = sin(angle);
  float x, z;
  for (int i = 0; i < A->rows; i++) {
    x = A->matrix[i][0];
    z = A->matrix[i][2];
    A->matrix[i][0] = cosf * x + sinf * z;
    A->matrix[i][2] = -sinf * x + cosf * z;
  }
}

void rotate_z(matrix_t *A, float angle) {
  float cosf = cos(angle);
  float sinf = sin(angle);
  float x, y;
  for (int i = 0; i < A->rows; i++) {
    x = A->matrix[i][0];
    y = A->matrix[i][1];
    A->matrix[i][0] = cosf * x - sinf * y;
    A->matrix[i][1] = sinf * x + cosf * y;
  }
}

void rotate_xyz(obj_t *obj, float angle_x, float angle_y, float angle_z) {
  float rad_x = 0.01745329251 * angle_x;
  float rad_y = 0.01745329251 * angle_y;
  float rad_z = 0.01745329251 * angle_z;
  move_to_zero(obj);
  rotate_x(&obj->vertexs, rad_x);
  rotate_y(&obj->vertexs, rad_y);
  rotate_z(&obj->vertexs, rad_z);
  move_to_back(obj);
}

void scale_x(matrix_t *A, float value) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] *= value;
  }
}

void scale_y(matrix_t *A, float value) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][1] *= value;
  }
}

void scale_z(matrix_t *A, float value) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][2] *= value;
  }
}

void scale_xyz(obj_t *obj, float x, float y, float z) {
  obj->offset[0] *= x;
  obj->offset[1] *= y;
  obj->offset[2] *= z;
  scale_x(&obj->vertexs, x);
  scale_y(&obj->vertexs, y);
  scale_z(&obj->vertexs, z);
}

void normalize(obj_t *obj) {
  float max_lenght = obj->vertexs.matrix[0][0] * obj->vertexs.matrix[0][0] +
                     obj->vertexs.matrix[0][1] * obj->vertexs.matrix[0][1] +
                     obj->vertexs.matrix[0][2] * obj->vertexs.matrix[0][2];
  float tmp, x, y, z;
  for (int i = 1; i < obj->vertexs.rows; i++) {
    x = obj->vertexs.matrix[i][0];
    y = obj->vertexs.matrix[i][1];
    z = obj->vertexs.matrix[i][2];
    tmp = x * x + y * y + z * z;
    if (tmp > max_lenght) {
      max_lenght = tmp;
    }
  }
  max_lenght = 1 / sqrtf(max_lenght);
  scale_xyz(obj, max_lenght, max_lenght, max_lenght);
}
