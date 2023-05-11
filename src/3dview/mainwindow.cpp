#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  sliderSetUp();
  connectSetUp();
  defSliders();
  defaultSettings();
  ui->OGLwidget->update();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::sliderSetUp() {
  ui->xRotate->setRange(-180, 180);
  ui->xRotate->setSingleStep(1);

  ui->yRotate->setRange(-180, 180);
  ui->yRotate->setSingleStep(1);

  ui->zRotate->setRange(-180, 180);
  ui->zRotate->setSingleStep(1);

  ui->xMove->setRange(-100, 100);
  ui->xMove->setSingleStep(1);

  ui->yMove->setRange(-100, 100);
  ui->yMove->setSingleStep(1);

  ui->zMove->setRange(-100, 100);
  ui->zMove->setSingleStep(1);

  ui->zoomSlider->setRange(1, 1000);
  ui->zMove->setSingleStep(1);

  ui->vertexSizeSlider->setRange(1, 25);
  ui->vertexSizeSlider->setSingleStep(1);

  ui->linesSizeSlider->setRange(1, 20);
  ui->linesSizeSlider->setSingleStep(1);
}

void MainWindow::connectSetUp() {
  connectMoveX();
  connectMoveY();
  connectMoveZ();
  connectRotateX();
  connectRotateY();
  connectRotateZ();
  connectZoom();
  connectFaces();
  connectVertexes();
  connectRadioButtn();
  connectSaveOpt();

  connect(ui->widgetBackGroundColor, SIGNAL(released()), (this),
          SLOT(backgroundColorChanged()));
  connect(ui->resetButton, SIGNAL(clicked()), (this), SLOT(resetValue()));
  connect(ui->openObjButton, SIGNAL(clicked()), this, SLOT(OpenFile()));
}

void MainWindow::connectMoveX() {
  connect(ui->xMove, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setXMove);
  connect(ui->xMText, SIGNAL(editingFinished()), (this), SLOT(xMoveTextEdit()));
  connect(ui->xMove, &QSlider::valueChanged, (this),
          &MainWindow::xMoveSliderValueChanged);
  connect(ui->OGLwidget, &GLWidget::xMoveChanged, ui->xMove,
          &QSlider::setValue);
}

void MainWindow::connectMoveY() {
  connect(ui->yMove, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setYMove);
  connect(ui->yMText, SIGNAL(editingFinished()), (this), SLOT(yMoveTextEdit()));
  connect(ui->yMove, &QSlider::valueChanged, (this),
          &MainWindow::yMoveSliderValueChanged);
  connect(ui->OGLwidget, &GLWidget::yMoveChanged, ui->yMove,
          &QSlider::setValue);
}

void MainWindow::connectMoveZ() {
  connect(ui->zMove, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setZMove);
  connect(ui->zMText, SIGNAL(editingFinished()), (this), SLOT(zMoveTextEdit()));
  connect(ui->zMove, &QSlider::valueChanged, (this),
          &MainWindow::zMoveSliderValueChanged);
}

void MainWindow::connectRotateX() {
  connect(ui->xRotate, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setXRotation);
  connect(ui->OGLwidget, &GLWidget::xRotationChanged, ui->xRotate,
          &QSlider::setValue);
  connect(ui->xRotateText, SIGNAL(editingFinished()), (this),
          SLOT(xRotateTextEdit()));
  connect(ui->xRotate, &QSlider::valueChanged, (this),
          &MainWindow::xRotateValueChanged);
}

void MainWindow::connectRotateY() {
  connect(ui->yRotate, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setYRotation);
  connect(ui->OGLwidget, &GLWidget::yRotationChanged, ui->yRotate,
          &QSlider::setValue);
  connect(ui->yRotateText, SIGNAL(editingFinished()), (this),
          SLOT(yRotateTextEdit()));
  connect(ui->yRotate, &QSlider::valueChanged, (this),
          &MainWindow::yRotateValueChanged);
}

void MainWindow::connectRotateZ() {
  connect(ui->zRotate, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setZRotation);
  connect(ui->OGLwidget, &GLWidget::zRotationChanged, ui->zRotate,
          &QSlider::setValue);
  connect(ui->zRotateText, SIGNAL(editingFinished()), (this),
          SLOT(zRotateTextEdit()));
  connect(ui->zRotate, &QSlider::valueChanged, (this),
          &MainWindow::zRotateValueChanged);
}

void MainWindow::connectZoom() {
  connect(ui->zoomSlider, &QSlider::valueChanged, ui->OGLwidget,
          &GLWidget::setZoom);
  connect(ui->zoomText, SIGNAL(editingFinished()), (this),
          SLOT(zoomTextEdit()));
  connect(ui->zoomSlider, &QSlider::valueChanged, (this),
          &MainWindow::zoomSliderValueChanged);
}

void MainWindow::connectVertexes() {
  connect(ui->vertexSizeSlider, &QSlider::valueChanged, (this),
          &MainWindow::vertexSize);
  connect(ui->colorVertex, SIGNAL(released()), (this),
          SLOT(vertexColorChanged()));
}

void MainWindow::connectFaces() {
  connect(ui->linesSizeSlider, &QSlider::valueChanged, (this),
          &MainWindow::linesSizeSliderChanged);
  connect(ui->colorFaces, SIGNAL(released()), (this),
          SLOT(edgesColorChanged()));
}

void MainWindow::connectRadioButtn() {
  connect(ui->ProjectionType_0, &QRadioButton::pressed, (this),
          &MainWindow::setCentral);
  connect(ui->ProjectionType_1, &QRadioButton::pressed, (this),
          &MainWindow::setParallel);
  connect(ui->LineStyle_0, &QRadioButton::pressed, (this),
          &MainWindow::lineSolid);
  connect(ui->LineStyle_1, &QRadioButton::pressed, (this),
          &MainWindow::lineDot);
  connect(ui->VertStyle_0, &QRadioButton::pressed, (this),
          &MainWindow::noneVert);
  connect(ui->VertStyle_1, &QRadioButton::pressed, (this),
          &MainWindow::circleVert);
  connect(ui->VertStyle_2, &QRadioButton::pressed, (this),
          &MainWindow::squareVert);
}

void MainWindow::connectSaveOpt() {
  // menu action
  connect(ui->actionBmp, &QAction::triggered, (this), &MainWindow::saveBmp);
  connect(ui->actionJpeg, &QAction::triggered, (this), &MainWindow::saveJpeg);
  connect(ui->actionGif, &QAction::triggered, (this), &MainWindow::saveGif);
  // timer for gif
  connect(&timer, &QTimer::timeout, (this), &MainWindow::createGif);
}

void MainWindow::defSliders() {
  ui->xRotate->setValue(0);
  ui->yRotate->setValue(0);
  ui->zRotate->setValue(0);
  ui->zoomSlider->setValue(100);
  ui->xMove->setValue(0);
  ui->yMove->setValue(0);
  ui->zMove->setValue(0);
  ui->xRotateText->setText(QString::number(0));
  ui->yRotateText->setText(QString::number(0));
  ui->zRotateText->setText(QString::number(0));
  ui->xMText->setText(QString::number(0));
  ui->yMText->setText(QString::number(0));
  ui->zMText->setText(QString::number(0));
}

void MainWindow::defaultSettings() {
  ui->linesSizeSlider->setValue(15);

  ui->linesSizeSlider->setValue(1);
  ui->OGLwidget->initSettings();
  ui->vertexSizeSlider->setValue(1);

  ui->VertStyle_0->toggle();
  ui->LineStyle_0->toggle();
  ui->ProjectionType_0->toggle();

  if (QFile::exists(pathConfig + "settings.conf")) {
    settingsFromConfig();
  }
}

void MainWindow::settingsFromConfig() {
  QSettings settings(pathConfig + "settings.conf", QSettings::IniFormat);
  QString colcode;
  settings.beginGroup("LineSet");

  ui->linesSizeSlider->setValue(settings.value("value").toInt());
  if (settings.value("lineType") == "true") {
    ui->LineStyle_0->toggle();
  } else {
    ui->LineStyle_1->toggle();
    ui->OGLwidget->lineMode = 1;
  }

  colcode = settings.value("color").toString();
  ui->OGLwidget->lineColor = colcode;
  ui->labelFacesColor->setStyleSheet("QLabel { background-color :" + colcode +
                                     " ; }");
  settings.endGroup();

  settings.beginGroup("VertexSet");

  colcode = settings.value("color").toString();
  ui->OGLwidget->pointColor = colcode;
  ui->labelVertColor->setStyleSheet("QLabel { background-color :" + colcode +
                                    " ; }");

  ui->vertexSizeSlider->setValue(settings.value("size").toInt());

  if (settings.value("VertStyle_none") == "true") {
    ui->VertStyle_0->toggle();
  } else if (settings.value("VertStyle_circle") == "true") {
    ui->VertStyle_1->toggle();
    ui->OGLwidget->pointMode = 1;
  } else if (settings.value("VertStyle_square") == "true") {
    ui->VertStyle_2->toggle();
    ui->OGLwidget->pointMode = 2;
  }
  settings.endGroup();
  settings.beginGroup("background");
  colcode = settings.value("color").toString();
  ui->OGLwidget->backgroundColor = colcode;
  ui->labelBackgroundColor->setStyleSheet(
      "QLabel { background-color :" + colcode + " ; }");
  settings.endGroup();
  settings.beginGroup("projection");
  if (settings.value("projection") == "true") {
    ui->ProjectionType_0->toggle();
  } else {
    ui->ProjectionType_1->toggle();
    ui->OGLwidget->projectionMode = 1;
  }
  settings.endGroup();
}

void MainWindow::saveSettings() {
  QSettings settings(pathConfig + "settings.conf", QSettings::IniFormat);
  settings.beginGroup("LineSet");
  settings.setValue("value", ui->linesSizeSlider->value());
  settings.setValue("color", ui->OGLwidget->lineColor);
  settings.setValue("lineType", ui->LineStyle_0->isChecked());
  settings.endGroup();
  settings.beginGroup("VertexSet");
  settings.setValue("color", ui->OGLwidget->pointColor);
  settings.setValue("size", ui->vertexSizeSlider->value());
  settings.setValue("VertStyle_none", ui->VertStyle_0->isChecked());
  settings.setValue("VertStyle_circle", ui->VertStyle_1->isChecked());
  settings.setValue("VertStyle_square", ui->VertStyle_2->isChecked());
  settings.endGroup();
  settings.beginGroup("background");
  settings.setValue("color", ui->OGLwidget->backgroundColor);
  settings.endGroup();
  settings.beginGroup("projection");
  settings.setValue("projection", ui->ProjectionType_0->isChecked());
  settings.endGroup();
}

void MainWindow::resetValue() {
  defaultSettings();
  ui->OGLwidget->update();
}

void MainWindow::xMoveSliderValueChanged(int value) {
  ui->xMText->setText(QString::number(value));
}

void MainWindow::yMoveSliderValueChanged(int value) {
  ui->yMText->setText(QString::number(value));
}

void MainWindow::zMoveSliderValueChanged(int value) {
  ui->zMText->setText(QString::number(value));
}

void MainWindow::linesSizeSliderChanged(int value) {
  ui->OGLwidget->lineSize = value;
  ui->OGLwidget->update();
}

void MainWindow::vertexSize(int value) {
  ui->OGLwidget->pointSize = value;
  ui->OGLwidget->update();
}

void MainWindow::xRotateValueChanged(int value) {
  ui->xRotateText->setText(QString::number(value));
}

void MainWindow::yRotateValueChanged(int value) {
  ui->yRotateText->setText(QString::number(value));
}

void MainWindow::zRotateValueChanged(int value) {
  ui->zRotateText->setText(QString::number(value));
}

void MainWindow::zoomSliderValueChanged(int value) {
  ui->zoomText->setText(QString::number(value));
}

int valNormalize(int val) {
  while (val > 180) {
    val -= 360;
  }
  while (val < -180) {
    val += 360;
  }
  return val;
}

void MainWindow::xRotateTextEdit() {
  int val = ui->xRotateText->text().toInt();
  val = valNormalize(val);
  ui->xRotate->setValue(val);
}

void MainWindow::yRotateTextEdit() {
  int val = ui->yRotateText->text().toInt();
  val = valNormalize(val);
  ui->yRotate->setValue(val);
}

void MainWindow::zRotateTextEdit() {
  int val = ui->zRotateText->text().toInt();
  val = valNormalize(val);
  ui->zRotate->setValue(val);
}

void MainWindow::xMoveTextEdit() {
  int val = ui->xMText->text().toInt();
  ui->xMove->setValue(val);
}

void MainWindow::yMoveTextEdit() {
  int val = ui->yMText->text().toInt();
  ui->yMove->setValue(val);
}

void MainWindow::zMoveTextEdit() {
  int val = ui->zMText->text().toInt();
  ui->zMove->setValue(val);
}

void MainWindow::zoomTextEdit() {
  int val = ui->zoomText->text().toInt();
  ui->zoomSlider->setValue(val);
}

void MainWindow::edgesColorChanged() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    ui->OGLwidget->lineColor = color;
    QVariant variant = color;
    QString colcode = variant.toString();
    ui->labelFacesColor->setStyleSheet("QLabel { background-color :" + colcode +
                                       " ; }");
  }
}

void MainWindow::vertexColorChanged() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    ui->OGLwidget->pointColor = color;
    QVariant variant = color;
    QString colcode = variant.toString();
    ui->labelVertColor->setStyleSheet("QLabel { background-color :" + colcode +
                                      " ; }");
  }
}

void MainWindow::backgroundColorChanged() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    ui->OGLwidget->backgroundColor = color;
    QVariant variant = color;
    QString colcode = variant.toString();
    ui->labelBackgroundColor->setStyleSheet(
        "QLabel { background-color :" + colcode + " ; }");
  }
}

void MainWindow::lineSolid() {
  ui->OGLwidget->lineMode = 0;
  ui->OGLwidget->update();
}

void MainWindow::lineDot() {
  ui->OGLwidget->lineMode = 1;
  ui->OGLwidget->update();
}

void MainWindow::setParallel() {
  ui->OGLwidget->projectionMode = 1;
  ui->OGLwidget->update();
}

void MainWindow::setCentral() {
  ui->OGLwidget->projectionMode = 0;
  ui->OGLwidget->update();
}

void MainWindow::circleVert() {
  ui->OGLwidget->pointMode = 1;
  ui->OGLwidget->update();
}

void MainWindow::squareVert() {
  ui->OGLwidget->pointMode = 2;
  ui->OGLwidget->update();
}

void MainWindow::noneVert() {
  ui->OGLwidget->pointMode = 0;
  ui->OGLwidget->update();
}

void MainWindow::OpenFile() {
  QFileDialog fileDialog;
  fileDialog.setWindowTitle(tr("Выберите .obj-файл"));
  fileDialog.setNameFilter(tr("(*.obj)"));
  fileDialog.setViewMode(QFileDialog::Detail);
  fileDialog.setFileMode(QFileDialog::ExistingFile);
  QStringList fileNames;
  if (fileDialog.exec()) {
    fileNames = fileDialog.selectedFiles();
    if (fileNames.size() > 0) {
      QString fileName = fileNames.at(0);
      QByteArray file_tmp = fileName.toLocal8Bit();
      char *input = file_tmp.data();
      defSliders();
      if (parser(input, &ui->OGLwidget->objData) != kOk) {
        status error;
        error.exec();
      } else {
        normalize(&ui->OGLwidget->objData);
        ui->statusbar->showMessage("файл: " + fileName);

        ui->numberOfFaces->setText(
            QString::number(ui->OGLwidget->objData.faces_count));
        ui->numberOfVerticies->setText(
            QString::number(ui->OGLwidget->objData.vertexs_count));
        ui->OGLwidget->initBuffers();
      }
    }
  }
}

void MainWindow::saveBmp() {
  QTime time = QTime::currentTime();
  QString curTime = time.toString("hh_mm_ss");
  ui->OGLwidget->grab().save(pathProject + "bmp_" + curTime + ".bmp");
}

void MainWindow::saveJpeg() {
  QTime time = QTime::currentTime();
  QString curTime = time.toString("hh_mm_ss");
  ui->OGLwidget->grab().save(pathProject + "jpg_" + curTime + ".jpg");
}

void MainWindow::saveGif() { timer.start(100); }

void MainWindow::createGif() {
  if (frame_count < 50) {
    gifFrames[frame_count] = ui->OGLwidget->grab().toImage().scaled(640, 480);
    frame_count++;
  } else {
    QGifImage gif(QSize(640, 480));
    for (int i = 0; i < frame_count; i++) {
      gif.addFrame(gifFrames[i], 0);
    }
    QTime time = QTime::currentTime();
    QString curTime = time.toString("hh_mm_ss");
    gif.save(pathProject + "gif_" + curTime + ".gif");
    timer.stop();
    frame_count = 0;
  }
}
