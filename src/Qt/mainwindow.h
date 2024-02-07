#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QSettings>
#include <QTime>
#include <iostream>
#include <string>

#include "myopenglwidget.h"

extern "C" {
#include "../C_part/back.h"
#include "gif.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  Model_data_t Data;
  int Data_exist = 0;

  double trans_x = 0;
  double trans_y = 0;
  double trans_z = 0;

  double rotate_x = 0;
  double rotate_y = 0;
  double rotate_z = 0;

  double color_red = 0;
  double color_green = 0;
  double color_blue = 0;

  double comp_scale = 1.0;

  int res_width = 640;
  int res_heigth = 480;

  void setup_start();

  QSettings *settings;

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_File_clicked();

  void on_doubleSpinBox_trans_x_valueChanged(double arg1);

  void on_doubleSpinBox_trans_y_valueChanged(double arg1);

  void on_doubleSpinBox_trans_z_valueChanged(double arg1);

  void on_doubleSpinBox_turn_x_valueChanged(double arg1);

  void on_doubleSpinBox_turn_y_valueChanged(double arg1);

  void on_doubleSpinBox_turn_z_valueChanged(double arg1);

  void on_doubleSpinBox_comp_scale_valueChanged(double arg1);

  void cleanup();

  void on_pushButton_bg_color_clicked();

  void on_pushButton_edge_color_clicked();

  void on_SpinBox_edge_size_valueChanged(int arg1);

  void on_comboBox_edge_currentIndexChanged(int index);

  void on_comboBox_vertices_currentIndexChanged(int index);

  void on_SpinBox_vert_size_valueChanged(int arg1);

  void on_pushButton_vertices_color_clicked();

  void on_comboBox_currentIndexChanged(int index);

  void save_settings();

  void load_settings();

  void save_gif(QString fileName);

  void on_pushButton_save_gif_clicked();

  void on_pushButton_Screenshot_clicked();

 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *myOpenGLWidget;
};
#endif  // MAINWINDOW_H
