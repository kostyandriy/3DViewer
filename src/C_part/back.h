#ifndef BACK_H
#define BACK_H

#ifdef __cplusplus
extern "C" {
#endif
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double x;
  double y;
  double z;
} points_t;

typedef struct {
  int amount_vert;
  points_t *cord;

  float MinMax_x[2];
  float MinMax_y[2];
  float MinMax_z[2];
} Vertex_t;

typedef struct {
  int *p;
  int amount_p;
} Polygon_t;

typedef struct {
  Vertex_t *v;
  Polygon_t *p;
  int amount_polygons;
} Model_data_t;

int Parse_file(Model_data_t *Data, char *path_to_file);
int parse_text(Model_data_t *Data, char *line);
int parse_vertex(Model_data_t *Data, char *line, size_t len);
void choose_MinMax(Model_data_t *Data);
int parse_face(Model_data_t *Data, char *line, size_t len);

void center(Model_data_t *Data);
void scale_start(Model_data_t *Data);
void scale_cords(Model_data_t *Data, double scale);
void motion(Model_data_t *Data, double move_x, double move_y, double move_z);
void turn(Model_data_t *Data, double grade, int axis);
void free_data(Model_data_t *data);
#ifdef __cplusplus
}
#endif

#endif  // BACK_H
