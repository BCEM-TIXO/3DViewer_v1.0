#include "s21_obj.h"

int init_obj(obj_t *obj) {
  memset(obj, 0, sizeof(obj_t));
  return 0;
}

void remove_obj(obj_t *obj) {
  free(obj->faces);
  s21_remove_matrix(&obj->vertexs);
  init_obj(obj);
}
