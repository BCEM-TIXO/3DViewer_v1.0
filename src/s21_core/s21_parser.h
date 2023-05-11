#ifndef SRC_S21_CORE_S21_PARCER_H
#define SRC_S21_CORE_S21_PARCER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_obj.h"
#include "s21_transformations.h"

#define MAX_STRING_LENGHT 4096

enum parser_status { kOpenFileErr = 1, kFileIncorrect };

int counts(FILE *file, obj_t *obj);

void get_v_vallues(char *line, int row, obj_t *obj);
int get_f_vallues(char *line, int *pos, obj_t *obj);

int parser(char *path_to_file, obj_t *obj);

#endif  // SRC_S21_CORE_S21_PARCER_H
