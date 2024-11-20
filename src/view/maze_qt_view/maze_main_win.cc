#include "maze_main_win.h"

#include <iostream>

#include "ui_maze_main_win.h"

MazeMainWin::MazeMainWin(s21::ControllerMaze *controller_)
    : ui_(new Ui::MazeMainWin) {
  ui_->setupUi(this);
  controller_obj_ = controller_;
  button_agregator_ = new ButtonLogic(ui_);
}

MazeMainWin::~MazeMainWin() {
  delete button_agregator_;
  delete ui_;
}

void MazeMainWin::on_button_load_clicked() {
  button_agregator_->Agregate(controller_obj_,
                              ButtonLogic::Procedure::OpenFile);
}

void MazeMainWin::on_button_save_clicked() {
  button_agregator_->Agregate(controller_obj_,
                              ButtonLogic::Procedure::SaveFile);
}

void MazeMainWin::on_button_generate_clicked() {
  button_agregator_->Agregate(controller_obj_,
                              ButtonLogic::Procedure::Generate);
}

void MazeMainWin::on_button_start_edu_clicked() {
  button_agregator_->Agregate(controller_obj_,
                              ButtonLogic::Procedure::FindRoute);
}

void MazeMainWin::on_button_generate_2_clicked() {}
