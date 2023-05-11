#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QSettings>
#include <QTimer>
#include <QVector>

#include "QtGifImage/src/gifimage/qgifimage.h"
#include "glwidget.h"
#include "status.h"

extern "C" {
#include "../s21_core/s21_core_viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void xMoveTextEdit();
  void yMoveTextEdit();
  void zMoveTextEdit();
  void xRotateTextEdit();
  void yRotateTextEdit();
  void zRotateTextEdit();
  void zoomTextEdit();
  void linesSizeSliderChanged(int value);
  void xRotateValueChanged(int value);
  void yRotateValueChanged(int value);
  void zRotateValueChanged(int value);
  void xMoveSliderValueChanged(int value);
  void yMoveSliderValueChanged(int value);
  void zMoveSliderValueChanged(int value);
  void edgesColorChanged();
  void vertexColorChanged();
  void backgroundColorChanged();
  void vertexSize(int value);
  void zoomSliderValueChanged(int value);
  void lineSolid();
  void lineDot();
  void setParallel();
  void setCentral();
  void noneVert();
  void circleVert();
  void squareVert();
  void OpenFile();
  void resetValue();
  void saveBmp();
  void saveJpeg();
  void saveGif();
  void createGif();

 private:
  Ui::MainWindow *ui;
  QImage gifFrames[50];
  QTimer timer;
  QString pathConfig = QDir::homePath() + "/.config/viewer/";
  QString pathProject = QDir::homePath() + "/viewer/";
  int frame_count = 0;
  void connectSetUp();
  void connectMoveX();
  void connectMoveY();
  void connectMoveZ();
  void connectRotateX();
  void connectRotateY();
  void connectRotateZ();
  void connectZoom();
  void connectFaces();
  void connectVertexes();
  void connectRadioButtn();
  void connectSaveOpt();
  void sliderSetUp();
  void defaultSettings();
  void settingsFromConfig();
  void defSliders();
  void saveSettings();
};
#endif  // MAINWINDOW_H
