// #ifndef MYOPENGLWIDGET_H
// #define MYOPENGLWIDGET_H

// #endif // MYOPENGLWIDGET_H

#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <GL/glu.h>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QtOpenGL>

extern "C" {
#include "../C_part/back.h"
}

class MyOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyOpenGLWidget(QWidget *parent = nullptr);

  int Paint_access = 0;
  // save in settings
  // {
  double bg_color_red = 0.5;
  double bg_color_green = 0;
  double bg_color_blue = 0.5;

  double edge_color_red = 1.0;
  double edge_color_green = 0.0;
  double edge_color_blue = 1.0;
  int edge_thin = 2;
  int edge_factor = 0;
  GLushort edge_pattern = 0xAAAA;

  double vertex_color_red = 0.0;
  double vertex_color_green = 0.0;
  double vertex_color_blue = 0.0;
  int vertex_size = 5;
  int vertex_factor = 0;
  // }

  int projection_type = 0;

  void setModelData(Model_data_t &data);

  void set_bg_color(QColor color);

  void set_edge_color(QColor color);
  void set_edge_thin(int arg1);
  void set_edge_type(int arg1);

  void set_vertex_type(int arg1);
  void set_vertex_size(int arg1);
  void set_vertex_color(QColor color);

  void set_projection_type(int arg1);

 protected:
  void initializeGL() override;
  void paintGL() override;
  Model_data_t Data;
};

#endif  // MYOPENGLWIDGET_H
