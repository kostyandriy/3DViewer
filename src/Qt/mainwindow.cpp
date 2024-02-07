#include "mainwindow.h"

#include "ui_mainwindow.h"

void MainWindow::setup_start() {
  ui->doubleSpinBox_comp_scale->setValue(1.00);
  ui->doubleSpinBox_trans_x->setValue(0.0);
  ui->doubleSpinBox_trans_y->setValue(0.0);
  ui->doubleSpinBox_trans_z->setValue(0.0);
  ui->doubleSpinBox_turn_x->setValue(0.0);
  ui->doubleSpinBox_turn_y->setValue(0.0);
  ui->doubleSpinBox_turn_z->setValue(0.0);

  Data_exist = 0;

  trans_x = 0;
  trans_y = 0;
  trans_z = 0;

  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;

  comp_scale = 1.0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  myOpenGLWidget = findChild<MyOpenGLWidget *>("widget");

  ui->doubleSpinBox_comp_scale->setValue(1.00);
  ui->doubleSpinBox_comp_scale->setSingleStep(0.1);
  ui->doubleSpinBox_comp_scale->setRange(0.1, 10);

  ui->doubleSpinBox_trans_x->setSingleStep(0.1);
  ui->doubleSpinBox_trans_x->setRange(-100.0, 100.0);

  ui->doubleSpinBox_trans_y->setSingleStep(0.1);
  ui->doubleSpinBox_trans_y->setRange(-100.0, 100.0);

  ui->doubleSpinBox_trans_z->setSingleStep(0.1);
  ui->doubleSpinBox_trans_z->setRange(-100.0, 100.0);

  ui->doubleSpinBox_turn_x->setRange(-360.0, 360.0);
  ui->doubleSpinBox_turn_y->setRange(-360.0, 360.0);
  ui->doubleSpinBox_turn_z->setRange(-360.0, 360.0);

  ui->SpinBox_edge_size->setValue(2);
  ui->SpinBox_edge_size->setSingleStep(1);
  ui->SpinBox_edge_size->setRange(1, 10);

  ui->SpinBox_vert_size->setValue(5);
  ui->SpinBox_vert_size->setSingleStep(1);
  ui->SpinBox_vert_size->setRange(1, 20);

  settings = new QSettings("21 school", "3D_Viewer", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  delete settings;
  delete ui;
}

void MainWindow::on_pushButton_File_clicked() {
  QString path = ui->lineEdit->text();
  int flag_path_error = 0;
  if (path.isEmpty() || path.length() > 100) {
    flag_path_error = 1;
  }
  if (!flag_path_error) {
    setup_start();
    int count_edges = 0;
    // Инициализация
    Data.v = (Vertex_t *)malloc(sizeof(Vertex_t));
    if (Data.v != NULL) {
      Data.p = NULL;
      Data.v->amount_vert = 0;
      Data.amount_polygons = 0;
      Data.v->cord = NULL;
      char *str = path.toUtf8().data();
      if (Parse_file(&Data, str)) {
        Data_exist = 1;
        ssize_t lastSlash = path.lastIndexOf('/');
        QString modelName = path;
        if (lastSlash != -1) {
          modelName = path.mid(lastSlash + 1);
        }
        for (int h = 0; h < Data.amount_polygons; h++) {
          count_edges += Data.p[h].amount_p;
        }

        ui->label_val_name->setText(modelName);
        ui->label_val_num_vert->setText(
            QString::number(Data.v->amount_vert, 'd', 0));
        ui->label_val_num_faces->setText(QString::number(count_edges, 'd', 0));

        center(&Data);
        scale_start(&Data);
        myOpenGLWidget->setModelData(Data);
      }
    }
  }
}

void MainWindow::on_doubleSpinBox_trans_x_valueChanged(double arg1) {
  if (Data_exist) {
    double move_x = arg1 - trans_x;
    trans_x = arg1;
    motion(&Data, move_x, 0, 0);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_trans_y_valueChanged(double arg1) {
  if (Data_exist) {
    double move_y = arg1 - trans_y;
    trans_y = arg1;
    motion(&Data, 0, move_y, 0);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_trans_z_valueChanged(double arg1) {
  if (Data_exist) {
    double move_z = arg1 - trans_z;
    trans_z = arg1;
    motion(&Data, 0, 0, move_z);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_turn_x_valueChanged(double arg1) {
  if (Data_exist) {
    double turn_x = arg1 - rotate_x;
    rotate_x = arg1;
    turn(&Data, turn_x, 0);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_turn_y_valueChanged(double arg1) {
  if (Data_exist) {
    double turn_y = arg1 - rotate_y;
    rotate_y = arg1;
    turn(&Data, turn_y, 1);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_turn_z_valueChanged(double arg1) {
  if (Data_exist) {
    double turn_z = arg1 - rotate_z;
    rotate_z = arg1;
    turn(&Data, turn_z, 2);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::on_doubleSpinBox_comp_scale_valueChanged(double arg1) {
  if (Data_exist) {
    double scale = arg1 / comp_scale;
    comp_scale = arg1;
    scale_cords(&Data, scale);
    myOpenGLWidget->setModelData(Data);
  }
}

void MainWindow::cleanup() {
  if (Data_exist) {
    free_data(&Data);
  }
}

void MainWindow::on_pushButton_bg_color_clicked() {
  QColor color = QColorDialog::getColor();
  color.setAlphaF(1.0);
  myOpenGLWidget->set_bg_color(color);
}

void MainWindow::on_pushButton_edge_color_clicked() {
  QColor color = QColorDialog::getColor();
  color.setAlphaF(1.0);
  myOpenGLWidget->set_edge_color(color);
}

void MainWindow::on_SpinBox_edge_size_valueChanged(int arg1) {
  myOpenGLWidget->set_edge_thin(arg1);
}

void MainWindow::on_comboBox_edge_currentIndexChanged(int index) {
  myOpenGLWidget->set_edge_type(index);
}

void MainWindow::on_comboBox_vertices_currentIndexChanged(int index) {
  myOpenGLWidget->set_vertex_type(index);
}

void MainWindow::on_SpinBox_vert_size_valueChanged(int arg1) {
  myOpenGLWidget->set_vertex_size(arg1);
}

void MainWindow::on_pushButton_vertices_color_clicked() {
  QColor color = QColorDialog::getColor();
  color.setAlphaF(1.0);
  myOpenGLWidget->set_vertex_color(color);
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  myOpenGLWidget->set_projection_type(index);
}

void MainWindow::save_settings() {
  settings->setValue("Settings_exist", 1);

  settings->setValue("projection_type", myOpenGLWidget->projection_type);

  settings->setValue("edge_factor", myOpenGLWidget->edge_factor);
  settings->setValue("edge_color_red", myOpenGLWidget->edge_color_red);
  settings->setValue("edge_color_green", myOpenGLWidget->edge_color_green);
  settings->setValue("edge_color_blue", myOpenGLWidget->edge_color_blue);
  settings->setValue("edge_thin", myOpenGLWidget->edge_thin);

  settings->setValue("vertex_factor", myOpenGLWidget->vertex_factor);
  settings->setValue("vertex_color_red", myOpenGLWidget->vertex_color_red);
  settings->setValue("vertex_color_green", myOpenGLWidget->vertex_color_green);
  settings->setValue("vertex_color_blue", myOpenGLWidget->vertex_color_blue);
  settings->setValue("vertex_size", myOpenGLWidget->vertex_size);

  settings->setValue("bg_color_red", myOpenGLWidget->bg_color_red);
  settings->setValue("bg_color_green", myOpenGLWidget->bg_color_green);
  settings->setValue("bg_color_blue", myOpenGLWidget->bg_color_blue);
}

void MainWindow::load_settings() {
  if (settings->value("Settings_exist").toInt()) {
    myOpenGLWidget->projection_type =
        settings->value("projection_type").toInt();
    ui->comboBox->setCurrentIndex(settings->value("projection_type").toInt());

    myOpenGLWidget->edge_factor = settings->value("edge_factor").toInt();
    if (settings->value("edge_factor").toInt() == 0) {
      ui->comboBox_edge->setCurrentIndex(0);
    } else {
      ui->comboBox_edge->setCurrentIndex(1);
    }

    myOpenGLWidget->edge_color_red =
        settings->value("edge_color_red").toFloat();
    myOpenGLWidget->edge_color_green =
        settings->value("edge_color_green").toFloat();
    myOpenGLWidget->edge_color_blue =
        settings->value("edge_color_blue").toFloat();

    myOpenGLWidget->edge_thin = settings->value("edge_thin").toInt();
    ui->SpinBox_edge_size->setValue(settings->value("edge_thin").toInt());

    myOpenGLWidget->vertex_factor = settings->value("vertex_factor").toInt();
    ui->comboBox_vertices->setCurrentIndex(
        settings->value("vertex_factor").toInt());

    myOpenGLWidget->vertex_color_red =
        settings->value("vertex_color_red").toFloat();
    myOpenGLWidget->vertex_color_green =
        settings->value("vertex_color_green").toFloat();
    myOpenGLWidget->vertex_color_blue =
        settings->value("vertex_color_blue").toFloat();

    myOpenGLWidget->vertex_size = settings->value("vertex_size").toInt();
    ui->SpinBox_vert_size->setValue(settings->value("vertex_size").toInt());

    myOpenGLWidget->bg_color_red = settings->value("bg_color_red").toFloat();
    myOpenGLWidget->bg_color_green =
        settings->value("bg_color_green").toFloat();
    myOpenGLWidget->bg_color_blue = settings->value("bg_color_blue").toFloat();
  }
}

void MainWindow::save_gif(QString fileName) {
  QImage img(ui->widget->size(), QImage::Format_RGBA8888), img640_480;
  QPainter painter(&img);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  QTime dieTime;
  GifWriter gif;
  QByteArray ba = fileName.toLocal8Bit();
  const char *c_str = ba.data();
  GifBegin(&gif, c_str, res_width, res_heigth, 10);

  for (int i = 1; i <= 50; ++i) {
    if (i % 10 == 0)
      ui->pushButton_save_gif->setText(QString::number(i / 10) + "s");
    ui->widget->render(&painter);
    img640_480 = img.scaled(QSize(res_width, res_heigth));
    GifWriteFrame(&gif, img640_480.bits(), res_width, res_heigth, 10);
    dieTime = QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
      QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
  }
  ui->pushButton_save_gif->setText("Gif");
  GifEnd(&gif);
  QMessageBox::information(this, "GIF READY", "GIF saved successfully.");
}

void MainWindow::on_pushButton_save_gif_clicked() {
  if (Data_exist) {
    QString name = "gif.gif";
    save_gif(name);
  } else {
    QMessageBox gif_fail;
    gif_fail.information(0, "", "Open model file to do screenshot");
  }
}

void MainWindow::on_pushButton_Screenshot_clicked() {
  if (Data_exist) {
    QString name = "";
    QImage img = myOpenGLWidget->grabFramebuffer();
    if (ui->comboBox_screen_type->currentIndex() == 0) {
      name = "Screenshot.jpeg";
    } else if (ui->comboBox_screen_type->currentIndex() == 1) {
      name = "Screenshot.bmp";
    }
    img.save(name);
    QMessageBox screen_succes;
    screen_succes.information(0, "", "Screenshot saved");
  } else {
    QMessageBox screen_fail;
    screen_fail.information(0, "", "Open model file to do screenshot");
  }
}
