#include "button_logic.h"

ButtonLogic::ButtonLogic(Ui::MazeMainWin* main_ui) {
  helper_ = new Helper;
  ui_ = main_ui;
  ui_->openGlView->SetHelper(helper_);
  ui_->openGLCave->SetHelper(helper_);
}

ButtonLogic::~ButtonLogic() { delete helper_; }

void ButtonLogic::Agregate(s21::ControllerMaze* controller,
                           Procedure procedure) {
  controller_obj_ = controller;
  if (controller_obj_ == nullptr) {
    return;
  }
  switch (procedure) {
    case Procedure::Generate:
      GenerateWork();
      break;
    case Procedure::OpenFile:
      OpenFileWork();
      break;
    case Procedure::SaveFile:
      SaveFileWork();
      break;
    case Procedure::FindRoute:
      RouteWork();
      break;
    default:
      break;
  }
}

void ButtonLogic::RouteWork() {
  if (controller_obj_->GetMaze() == nullptr) {
    return;
  }
  s21::ModelMaze::MazeRequest opt;
  opt.opt_ion = s21::ModelMaze::MazeRequest::FindRoute;
  s21::Coordinate start = {
      (short unsigned int)(helper_->m_pos_a.y() / helper_->lineLength_y_),
      (short unsigned int)(helper_->m_pos_a.x() / helper_->lineLength_x_)};
  s21::Coordinate end = {
      (short unsigned int)(helper_->m_pos_b.y() / helper_->lineLength_y_),
      (short unsigned int)(helper_->m_pos_b.x() / helper_->lineLength_x_)};
  qDebug() << "start: " << start.row << " " << start.col << " "
           << "end: " << end.row << " " << end.col;

  opt.A_coord = start;
  opt.B_coord = end;

  if (controller_obj_->WantMaze(opt)) {
    helper_->SetMaze(controller_obj_->GetMaze());
  }
  ui_->openGlView->update();
  ui_->openGLCave->update();
}

void ButtonLogic::OpenFileWork() {
  QString fileName2 = QFileDialog::getOpenFileName(
      this, tr("Open MAZE File"), data_path_1_, tr("MAZE Files (*.mz)"));
  if (fileName2 != "") {
    data_path_1_ = fileName2;
    ui_->label_6->setText(
        fileName2.right(fileName2.size() - fileName2.lastIndexOf("/")));
  } else {
    error_message("Нет файла");
    return;
  }
  s21::ModelMaze::MazeRequest opt;
  opt.opt_ion = s21::ModelMaze::MazeRequest::OpenFile;
  opt.file_name = fileName2.toStdString();
  if (controller_obj_->WantMaze(opt)) {
    helper_->SetMaze(controller_obj_->GetMaze());
  }
  ui_->maze_rows->setValue(controller_obj_->GetMaze()->Size().maze_rows);
  ui_->maze_cols->setValue(controller_obj_->GetMaze()->Size().maze_cols);
  ui_->openGlView->update();
  ui_->openGLCave->update();
}

void ButtonLogic::SaveFileWork() {
  QString fileName2 = QFileDialog::getSaveFileName(
      this, tr("Save MAZE File"), data_path_1_, tr("MAZE Files (*.mz)"));
  if (fileName2 != "") {
    data_path_1_ = fileName2;
    ui_->label_6->setText(
        fileName2.right(fileName2.size() - fileName2.lastIndexOf("/")));
  } else {
    error_message("Нет файла");
    return;
  }
  s21::ModelMaze::MazeRequest opt;
  opt.opt_ion = s21::ModelMaze::MazeRequest::SaveFile;
  opt.file_name = fileName2.toStdString();
  if (controller_obj_->WantMaze(opt)) {
    helper_->SetMaze(controller_obj_->GetMaze());
  }
}

void ButtonLogic::GenerateWork() {
  s21::ModelMaze::MazeRequest opt;
  opt.size.maze_rows = ui_->maze_rows->value();
  opt.size.maze_cols = ui_->maze_cols->value();
  opt.opt_ion = s21::ModelMaze::MazeRequest::Generate;
  if (controller_obj_->WantMaze(opt)) {
    helper_->SetMaze(controller_obj_->GetMaze());
  }
  ui_->openGlView->update();
  ui_->openGLCave->update();
}

void ButtonLogic::error_message(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(500, 200);
  messageBox.information(0, "Info", message);
}
