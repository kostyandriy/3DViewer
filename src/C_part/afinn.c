#include "back.h"

void center(Model_data_t *Data) {
  double center[3] = {0, 0, 0};
  center[0] =
      Data->v->MinMax_x[0] + (Data->v->MinMax_x[1] - Data->v->MinMax_x[0]) / 2;
  center[1] =
      Data->v->MinMax_y[0] + (Data->v->MinMax_y[1] - Data->v->MinMax_y[0]) / 2;
  center[2] =
      Data->v->MinMax_z[0] + (Data->v->MinMax_z[1] - Data->v->MinMax_z[0]) / 2;
  for (int i = 0; i < Data->v->amount_vert; i++) {
    Data->v->cord[i].x = Data->v->cord[i].x - center[0];
    Data->v->cord[i].y = Data->v->cord[i].y - center[1];
    Data->v->cord[i].z = Data->v->cord[i].z - center[2];
  }
  choose_MinMax(Data);
}

void scale_start(Model_data_t *Data) {
  double spacing[3] = {0, 0, 0};
  spacing[0] = Data->v->MinMax_x[1] - Data->v->MinMax_x[0];
  spacing[1] = Data->v->MinMax_y[1] - Data->v->MinMax_y[0];
  spacing[2] = Data->v->MinMax_z[1] - Data->v->MinMax_z[0];
  double dmax = spacing[0];
  for (int i = 1; i < 3; i++) {
    if (spacing[i] > dmax) dmax = spacing[i];
  }
  double scale = (0.8 - (0.8 * (-1))) / dmax;
  scale_cords(Data, scale);
}

void scale_cords(Model_data_t *Data, double scale) {
  for (int i = 0; i < Data->v->amount_vert; i++) {
    Data->v->cord[i].x *= scale;
    Data->v->cord[i].y *= scale;
    Data->v->cord[i].z *= scale;
  }
}

void motion(Model_data_t *Data, double move_x, double move_y, double move_z) {
  for (int i = 0; i < Data->v->amount_vert; i++) {
    Data->v->cord[i].x += move_x;
    Data->v->cord[i].y += move_y;
    Data->v->cord[i].z += move_z;
  }
}

// axis = 0 -> вокруг x,
// axis = 1 -> вокруг y,
// axis = 2 -> вокруг z
void turn(Model_data_t *Data, double grade, int axis) {
  for (int i = 0; i < Data->v->amount_vert; i++) {
    double x = Data->v->cord[i].x;
    double y = Data->v->cord[i].y;
    double z = Data->v->cord[i].z;

    if (axis == 0) {
      Data->v->cord[i].y =
          y * cos(M_PI / 180 * grade) - z * sin(M_PI / 180 * grade);
      Data->v->cord[i].z =
          z * cos(M_PI / 180 * grade) + y * sin(M_PI / 180 * grade);
    } else if (axis == 1) {
      Data->v->cord[i].x =
          x * cos(M_PI / 180 * grade) + z * sin(M_PI / 180 * grade);
      Data->v->cord[i].z =
          z * cos(M_PI / 180 * grade) - x * sin(M_PI / 180 * grade);
    } else if (axis == 2) {
      Data->v->cord[i].x =
          x * cos(M_PI / 180 * grade) + y * sin(M_PI / 180 * grade);
      Data->v->cord[i].y =
          y * cos(M_PI / 180 * grade) - x * sin(M_PI / 180 * grade);
    }
  }
}
