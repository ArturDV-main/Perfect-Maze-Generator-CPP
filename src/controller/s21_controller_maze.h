#ifndef S21_CONTROLLER_mazeE_
#define S21_CONTROLLER_mazeE_

#include "../model/s21_model_maze.h"

namespace s21 {
class ControllerMaze {
 public:
  ControllerMaze() = default;
  ControllerMaze(const ControllerMaze&) = delete;
  ControllerMaze(ControllerMaze&&) = delete;
  ~ControllerMaze() = default;
  ControllerMaze& operator=(const ControllerMaze&) = delete;
  ControllerMaze& operator=(ControllerMaze&&) = delete;
  void SetModel(s21::ModelMaze* model) { model_ = model; }
  const s21::Maze * GetMaze() const {
    const s21::Maze * val = model_->GetMaze();
    return val;
  }
 private:
  s21::ModelMaze* model_;

};
}  // namespace s21

#endif  // S21_CONTROLLER_mazeE_
