#include "s21_parser.h"

int counts(FILE *file, obj_t *obj) {
  int status = kOk;
  char buff[MAX_STRING_LENGHT] = {0};
  int tmp_v = 0, tmp_f = 0, tmp = 0, flag = 0;
  char *isstr;
  while (feof(file) == 0 && status == kOk) {
    fgets(buff, MAX_STRING_LENGHT - 1, file);
    if (strncmp(buff, "v ", 2) == 0) {
      tmp_v++;
    }
    if (strncmp(buff, "f ", 2) == 0) {
      tmp_f++;
      isstr = buff + 2;
      flag = 0;
      while (*isstr != '\0') {
        if (isspace(*isstr) && *(isstr + 1) != '\n') {
          tmp++;
          flag = 1;
        }
        isstr++;
      }
      if (flag == 0) {
        status = kFileIncorrect;
      }
    }
    buff[0] = '\0';
  }
  if (tmp_v == 0 || tmp_f == 0 || tmp == 0) {
    status = kFileIncorrect;
  } else {
    obj->vertexs_count = tmp_v;
    obj->faces_count = tmp_f;
    obj->faces_lenght = tmp;
    s21_create_matrix(obj->vertexs_count, 4, &obj->vertexs);
    obj->faces = (unsigned *)malloc(sizeof(unsigned) * (obj->faces_lenght * 2));
  }
  return status;
}

void get_v_vallues(char *line, int row, obj_t *obj) {
  char *end = NULL;
  if (obj->vertexs.matrix != NULL) {
    for (int i = 0; i < 4; i++) {
      obj->vertexs.matrix[row][i] = strtod(line, &end);
      // if (row == 0 && i != 3) {
      //   obj->xyz_max[i] = fabsf(obj->vertexs.matrix[row][i]);
      // }
      if (i == 3 && end == line) {
        obj->vertexs.matrix[row][i] = 1;
      }
      line = end;
    }
    // if (row != 0 && obj->xyz_max[0] < fabsf(obj->vertexs.matrix[row][0]) &&
    // obj->xyz_max[1] < fabsf(obj->vertexs.matrix[row][1]) && obj->xyz_max[2] <
    // fabsf(obj->vertexs.matrix[row][2])) {
    //     obj->xyz_max[0] = obj->vertexs.matrix[row][0];
    //     obj->xyz_max[1] = obj->vertexs.matrix[row][2];
    //     obj->xyz_max[1] = obj->vertexs.matrix[row][2];
    //   }
  }
}

int get_f_vallues(char *line, int *pos, obj_t *obj) {
  int status = kOk;
  char *end = line;
  int i = *pos;
  int tmp;
  //  char *l = line;
  if (obj->faces != NULL) {
    for (; *line != '\0' && status == kOk;) {
      tmp = strtol(line, &end, 10);
      if (line == end) {
        break;
      }
      while (!isspace(*end)) {
        end++;
      }
      if (tmp != 0) {
        if (tmp < 0) {
          status = kFileIncorrect;
        }
        obj->faces[i] = tmp - 1;
        i++;
        if (i - *pos != 1) {
          obj->faces[i] = tmp - 1;
          i++;
        }
      }
      line = end;
    }
    obj->faces[i] = obj->faces[*pos];
    i++;
    *pos = i;
  }
  return status;
}

int get_vf_vallues(FILE *file, obj_t *obj) {
  char buff[MAX_STRING_LENGHT];
  int row = 0;
  int pos = 0;
  // int tmp = 0;
  int i = 0;
  int status = kOk;
  while (feof(file) == 0 && status == kOk) {
    fgets(buff, MAX_STRING_LENGHT - 1, file);
    if (strncmp(buff, "v ", 2) == 0) {
      get_v_vallues(buff + 2, row, obj);
      row++;
    }
    if (strncmp(buff, "f ", 2) == 0) {
      status = get_f_vallues(buff + 2, &pos, obj);
      i++;
      //    tmp = pos;
    }
    buff[0] = '\0';
  }
  return status;
  // obj->max = 1 / sqrtf(obj->xyz_max[0] * obj->xyz_max[0] + obj->xyz_max[1] *
  // obj->xyz_max[1] + obj->xyz_max[2] * obj->xyz_max[2]); scale_xyz(obj,
  // obj->max, obj->max, obj->max);
}

int parser(char *path_to_file, obj_t *obj) {
  int status = kOk;
  init_obj(obj);
  FILE *file = fopen(path_to_file, "r");
  if (file == NULL) {
    status = kOpenFileErr;
  } else {
    init_obj(obj);
    status = counts(file, obj);
    if (status == kOk) {
      rewind(file);
      status = get_vf_vallues(file, obj);
      // normalize(obj);
    }
    fclose(file);
  }
  return status;
}
