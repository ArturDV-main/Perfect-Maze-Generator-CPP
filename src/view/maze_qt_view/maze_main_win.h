#ifndef MazeMainWin_H_
#define MazeMainWin_H_

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

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeMainWin;
}
QT_END_NAMESPACE

class MazeMainWin : public QMainWindow {
  Q_OBJECT

 public slots:
 public:
  MazeMainWin(QWidget *parent = nullptr);
  ~MazeMainWin();
  void SetControllerObj(s21::ControllerMaze *controller_obj) {
    controller_obj_ = controller_obj;
  }

 private slots:

  void on_button1_set_data_clicked();

  void on_button2_load_data_clicked();

  void on_button3_add_tests_clicked();

  void on_button4_load_tests_clicked();

  void on_button5_start_edu_clicked();

//  void on_button6_graph_clicked();

 private:

// Varebles
  QGraphicsScene *scene_{};
  s21::ControllerMaze *controller_obj_{};
  Ui::MazeMainWin *ui_{};

//  QTimer *m_timer_{};
//  QPushButton *button_blink_{};
  QString data_path_1_{};
  QString file_name_{};
  bool set_data_1_{}, load_data_2_{}, add_tests_3_{}, load_tests_4_{},
      load_image_5_{};
//  size_t frame_counter_{};
//  QImage personal_image_{};

//  Methods
  void error_message(QString message);
};
#endif  // MazeMainWin_H_
