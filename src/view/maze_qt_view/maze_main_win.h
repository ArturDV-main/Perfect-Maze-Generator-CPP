#ifndef MazeMainWin_H_
#define MazeMainWin_H_

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "./scenegl.h"
#include "button_logic.h"
#include "helpergl.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MazeMainWin;
}
QT_END_NAMESPACE

class MazeMainWin : public QMainWindow {
  Q_OBJECT

 public slots:
 public:
  //  MazeMainWin(QWidget *parent = nullptr, s21::ControllerMaze *controller_ =
  //  nullptr);
  MazeMainWin(s21::ControllerMaze *controller_);
  ~MazeMainWin();
  void SetControllerObj(s21::ControllerMaze *controller_obj) {
    controller_obj_ = controller_obj;
  }

 private slots:

  void on_button_load_clicked();

  void on_button_save_clicked();

  void on_button_generate_clicked();

  void on_button_start_edu_clicked();

  void on_button_generate_2_clicked();

 private:
  // Varebles
  s21::ControllerMaze *controller_obj_{};
  Ui::MazeMainWin *ui_{};
  ButtonLogic *button_agregator_{};

  //  Methods
};
#endif  // MazeMainWin_H_
