#ifndef BUTTON_LOGIC_H
#define BUTTON_LOGIC_H

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "../../controller/s21_controller_maze.h"
#include "helpergl.h"
#include "ui_maze_main_win.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class ButtonLogic;
}
QT_END_NAMESPACE

class ButtonLogic : public QMainWindow {
  Q_OBJECT
 public:
  enum Procedure { Generate, OpenFile, SaveFile, FindRoute, GenerateTest };
  ButtonLogic(Ui::MazeMainWin *main_ui);
  ~ButtonLogic();

  void Agregate(s21::ControllerMaze *controller, Procedure procedure);

  void RouteWork();

  void error_message(QString message);

 private slots:

 private:
  void File(Procedure variant);
  void OpenFileWork();
  void SaveFileWork();
  void GenerateWork();
  QString data_path_1_;
  s21::ControllerMaze *controller_obj_;
  Ui::MazeMainWin *ui_;
  int maze_variant_{};
  Helper *helper_{};
};

#endif  // BUTTON_LOGIC_H
