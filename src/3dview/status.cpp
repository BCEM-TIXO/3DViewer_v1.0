#include "status.h"

#include "ui_status.h"

status::status(QWidget *parent) : QDialog(parent), ui(new Ui::status) {
  this->setFixedSize(QSize(450, 125));
  ui->setupUi(this);
}

status::~status() { delete ui; }

void status::on_exitButton_clicked() { status::close(); }
