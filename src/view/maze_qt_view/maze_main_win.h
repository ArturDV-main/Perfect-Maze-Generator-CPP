#ifndef MLPMAINWIN_H_
#define MLPMAINWIN_H_

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStyle>
#include <QTime>
#include <QTimer>
#include <exception>

#include "../../controller/s21_controller_maze.h"
#include "s21_tablet.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MlpMainWin;
}
QT_END_NAMESPACE

class MlpMainWin : public QMainWindow {
  Q_OBJECT

 public slots:

 public:
  MlpMainWin(QWidget *parent = nullptr);
  ~MlpMainWin();
  void SetControllerObj(s21::ControllerPerceptron *controller_obj) {
    controller_obj_ = controller_obj;
  }

 private slots:
  void Toggle();

  void on_button1_set_data_clicked();

  void on_button2_load_data_clicked();

  void on_button3_add_tests_clicked();

  void on_button4_load_tests_clicked();

  void on_button5_start_edu_clicked();

  void on_button6_graph_clicked();

 private:
  QGraphicsScene *scene_;
  s21::ControllerPerceptron *controller_obj_{};
  Ui::MlpMainWin *ui_{};
  QTimer *m_timer_{};
  QPushButton *button_blink_{};
  QString data_path_1_{};
  QString fileName{};
  bool set_data_1_{}, load_data_2_{}, add_tests_3_{}, load_tests_4_{},
      load_image_5_{};
  //  QLabel *m_label;
  size_t frame_counter_{};
  QGraphicsPixmapItem *pixmapItem{};
  //  bool m_isChecked = false;
  QImage personal_image_;
  //  !!!!!!!
  void TabletOpen();
  void Paint();
  void BlinkingButton();
  void BlinkLogic();
  void error_message(QString message);
};
#endif  // MLPMAINWIN_H_
