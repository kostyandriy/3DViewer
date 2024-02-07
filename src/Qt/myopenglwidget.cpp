#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void MyOpenGLWidget::setModelData(Model_data_t &data) {
  Data = data;
  Paint_access = 1;
  update();
}

void MyOpenGLWidget::set_bg_color(QColor color) {
  bg_color_red = color.redF();
  bg_color_green = color.greenF();
  bg_color_blue = color.blueF();
  update();
}

void MyOpenGLWidget::set_edge_color(QColor color) {
  edge_color_red = color.redF();
  edge_color_green = color.greenF();
  edge_color_blue = color.blueF();
  update();
}

void MyOpenGLWidget::set_edge_thin(int arg1) {
  edge_thin = arg1;
  update();
}

void MyOpenGLWidget::set_edge_type(int arg1) {
  edge_factor = arg1 * 7;
  update();
}

void MyOpenGLWidget::set_vertex_type(int arg1) {
  vertex_factor = arg1;
  update();
}

void MyOpenGLWidget::set_vertex_size(int arg1) {
  vertex_size = arg1;
  update();
}

void MyOpenGLWidget::set_vertex_color(QColor color) {
  vertex_color_red = color.redF();
  vertex_color_green = color.greenF();
  vertex_color_blue = color.blueF();
  update();
}

void MyOpenGLWidget::set_projection_type(int arg1) {
  projection_type = arg1;
  update();
}

void MyOpenGLWidget::initializeGL() {
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->initializeOpenGLFunctions();
}

void MyOpenGLWidget::paintGL() {
  glClearColor(bg_color_red, bg_color_green, bg_color_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (Paint_access) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projection_type == 0) {
      gluPerspective(45.0f, static_cast<float>(width()) / height(), 0.1f,
                     100.0f);
      gluLookAt(2, 2, -4, 0, 0, 0, 0, 1, 0);
    } else if (projection_type == 1) {
      glOrtho(-2, 2, -2, 2, -5, 5);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < Data.amount_polygons; i++) {
      glLineWidth(edge_thin);
      if (edge_factor != 0) {
        glLineStipple(edge_factor, edge_pattern);
        glEnable(GL_LINE_STIPPLE);
      }
      glBegin(GL_LINE_LOOP);
      glColor3f(edge_color_red, edge_color_green, edge_color_blue);
      for (int j = 0; j < Data.p[i].amount_p; j++) {
        glVertex3d(Data.v->cord[Data.p[i].p[j] - 1].x,
                   Data.v->cord[Data.p[i].p[j] - 1].y,
                   Data.v->cord[Data.p[i].p[j] - 1].z);
      }
      glEnd();
      if (edge_factor != 0) {
        glDisable(GL_LINE_STIPPLE);
      }
    }

    if (vertex_factor != 0) {
      for (int i = 0; i < Data.amount_polygons; i++) {
        glPointSize(vertex_size);
        glEnable(GL_BLEND);
        if (vertex_factor == 1) {
          glDisable(GL_POINT_SMOOTH);
        }
        if (vertex_factor == 2) {
          glEnable(GL_POINT_SMOOTH);
        }
        glBegin(GL_POINTS);
        glColor3f(vertex_color_red, vertex_color_green, vertex_color_blue);
        for (int j = 0; j < Data.p[i].amount_p; j++) {
          glVertex3d(Data.v->cord[Data.p[i].p[j] - 1].x,
                     Data.v->cord[Data.p[i].p[j] - 1].y,
                     Data.v->cord[Data.p[i].p[j] - 1].z);
        }
        glEnd();
        glDisable(GL_BLEND);
      }
    }
  }
}
