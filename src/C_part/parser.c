#include "back.h"

int Parse_file(Model_data_t *Data, char *path_to_file) {
  int res = 0;
  size_t len = 0;
  int flag_ok = 1;
  FILE *fp = fopen(path_to_file, "r");
  if (fp) {
    char *str = NULL;
    while (getline(&str, &len, fp) != -1 && flag_ok != -1) {
      flag_ok = parse_text(Data, str);
    }
    free(str);
    fclose(fp);
  }
  if (flag_ok == 1) res = 1;

  return res;
}

int parse_text(Model_data_t *Data, char *line) {
  int res = 0;
  int flag_found = 0;
  size_t length_str = strlen(line);
  if (length_str == 0) {
    flag_found = 1;
    res = 1;
  }
  for (size_t i = 0; i < length_str && !flag_found; i++) {
    if (line[0] == 'v' && line[1] == ' ') {
      res = parse_vertex(Data, line, length_str);
      flag_found = 1;
    }
    if (line[0] == 'f' && line[1] == ' ') {
      res = parse_face(Data, line, length_str);
      flag_found = 1;
    }
  }
  return res;
}

int parse_vertex(Model_data_t *Data, char *line, size_t len) {
  double cord[3] = {0, 0, 0};
  int res = 0;
  int count = 0;
  for (size_t i = 1; i < len; i++) {
    if (line[i] == ' ' && line[i + 1] >= '0' && line[i + 1] <= '9' &&
        count <= 2) {
      cord[count] = atof(line + i + 1);
      if (count < 2) count++;
    }
    if (line[i] == ' ' && line[i + 1] == '-' && line[i + 2] >= '0' &&
        line[i + 2] <= '9' && count <= 2) {
      cord[count] = atof(line + i + 1);
      if (count < 2) count++;
    }
  }
  if (count == 2) {
    Data->v->cord = (points_t *)realloc(
        Data->v->cord, (Data->v->amount_vert + 1) * sizeof(points_t));
    if (Data->v->cord != NULL) {
      Data->v->amount_vert++;
      Data->v->cord[Data->v->amount_vert - 1].x = cord[0];
      Data->v->cord[Data->v->amount_vert - 1].y = cord[1];
      Data->v->cord[Data->v->amount_vert - 1].z = cord[2];
      choose_MinMax(Data);
      res = 1;
    } else {
      res = -1;
    }
  }
  return res;
}

void choose_MinMax(Model_data_t *Data) {
  for (int j = 0; j < Data->v->amount_vert; j++) {
    if (j == 0) {
      for (int i = 0; i < 2; i++) {
        Data->v->MinMax_x[i] = Data->v->cord[j].x;
        Data->v->MinMax_y[i] = Data->v->cord[j].y;
        Data->v->MinMax_z[i] = Data->v->cord[j].z;
      }
    }
    if (j > 0) {
      if (Data->v->cord[j].x < Data->v->MinMax_x[0])
        Data->v->MinMax_x[0] = Data->v->cord[j].x;
      if (Data->v->cord[j].y < Data->v->MinMax_y[0])
        Data->v->MinMax_y[0] = Data->v->cord[j].y;
      if (Data->v->cord[j].z < Data->v->MinMax_z[0])
        Data->v->MinMax_z[0] = Data->v->cord[j].z;

      if (Data->v->cord[j].x > Data->v->MinMax_x[1])
        Data->v->MinMax_x[1] = Data->v->cord[j].x;
      if (Data->v->cord[j].y > Data->v->MinMax_y[1])
        Data->v->MinMax_y[1] = Data->v->cord[j].y;
      if (Data->v->cord[j].z > Data->v->MinMax_z[1])
        Data->v->MinMax_z[1] = Data->v->cord[j].z;
    }
  }
}

int parse_face(Model_data_t *Data, char *line, size_t len) {
  int res = 0;
  Data->p = (Polygon_t *)realloc(
      Data->p, (Data->amount_polygons + 1) * sizeof(Polygon_t));
  if (Data->p != NULL) {
    Data->p[Data->amount_polygons].p = NULL;
    Data->p[Data->amount_polygons].amount_p = 0;
    for (size_t i = 1; i < len; i++) {
      if (line[i] == ' ' && line[i + 1] >= '0' && line[i + 1] <= '9') {
        Data->p[Data->amount_polygons].p = (int *)realloc(
            Data->p[Data->amount_polygons].p,
            (Data->p[Data->amount_polygons].amount_p + 1) * sizeof(int));
        if (Data->p[Data->amount_polygons].p != NULL) {
          Data->p[Data->amount_polygons]
              .p[Data->p[Data->amount_polygons].amount_p] = atoi(line + i + 1);
          Data->p[Data->amount_polygons].amount_p++;
          res = 1;
        }
      }
    }
  }
  Data->amount_polygons++;

  return res;
}

void free_data(Model_data_t *data) {
  if (data->v != NULL) {
    free(data->v->cord);
    free(data->v);
  }
  if (data->p != NULL) {
    for (int i = 0; i < data->amount_polygons; i++) {
      free(data->p[i].p);
    }
    free(data->p);
  }
}
