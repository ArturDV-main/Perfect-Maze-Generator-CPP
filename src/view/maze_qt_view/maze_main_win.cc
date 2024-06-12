#include "maze_main_win.h"

#include "ui_maze_main_win.h"

MazeMainWin::MazeMainWin(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MazeMainWin) {
  ui_->setupUi(this);
  scene_ = new QGraphicsScene(this);
  ui_->graphicsView->setScene(scene_);
}

MazeMainWin::~MazeMainWin() {
  delete ui_;
  delete scene_;
}

void MazeMainWin::on_button1_set_data_clicked() {
  QString fileName2 = QFileDialog::getOpenFileName(
      this, tr("Open MAZE File"), data_path_1_, tr("MAZE Files (*.mz)"));
  if (fileName2 != "") {
    data_path_1_ = fileName2;
    try {
      // controller_obj_->OpenCsv(data_path_1_.toStdString(), 784);
      // set_data_1_ = true;
      // load_image_5_ = false;
      // BlinkLogic();
      // ui_->textBrowser->setText(
      //     QString::number(controller_obj_->GetCsv()->size()));
//      Paint();
    } catch (std::exception& e) {
      error_message(e.what());
    }
  } else {
    error_message("Нет файла");
  }
}

void MazeMainWin::on_button2_load_data_clicked() {
  load_data_2_ = true;
}

void MazeMainWin::on_button3_add_tests_clicked() {
  add_tests_3_ = true;
}

void MazeMainWin::on_button4_load_tests_clicked() {
  load_tests_4_ = true;
}

void MazeMainWin::on_button5_start_edu_clicked() {
  set_data_1_ = false;
  load_data_2_ = false;
  add_tests_3_ = false;
  load_tests_4_ = false;
}

void MazeMainWin::error_message(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(500, 200);
  messageBox.information(0, "Info", message);
}
