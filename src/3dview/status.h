#ifndef STATUS_H
#define STATUS_H

#include <QDialog>

namespace Ui {
class status;
}

class status : public QDialog {
  Q_OBJECT

 public:
  explicit status(QWidget *parent = nullptr);
  ~status();

 private:
  Ui::status *ui;

 private slots:
  void on_exitButton_clicked();
};

#endif  // STATUS_H
