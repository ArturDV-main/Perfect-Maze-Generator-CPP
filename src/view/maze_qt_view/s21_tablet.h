#ifndef MAZE_S21_TABLET_H_
#define MAZE_S21_TABLET_H_

#include <QDialog>

#include "maze_drawing_widget.h"

namespace Ui {
class Tablet;
}

class Tablet : public QDialog {
  Q_OBJECT

 public:
  explicit Tablet(QWidget *parent = nullptr, QImage *img = nullptr);
  ~Tablet();

 private slots:
  void on_pushButton_clicked();

 private:
  QWidget *parent_;
  QImage *img_;
  Ui::Tablet *ui;
};

#endif  // S21_TABLET_H_
