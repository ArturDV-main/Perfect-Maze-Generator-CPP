#ifndef S21_CONTROLLER_MAZE_H_
#define S21_CONTROLLER_MAZE_H_

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

  // Returns a pointer to the maze. Returns nullptr if the model is not set.
  s21::Maze* GetMaze() {
    if (model_ == nullptr) {
      return nullptr;
    }
    return model_->GetMaze();
  }

  //  Generates a maze with the given options.
  //  Returns true if the maze is generated. Returns false if the model is not
  //  set.
  bool WantMaze(ModelMaze::MazeRequest request) {
    if (model_ == nullptr) {
      return false;
    }
    return model_->WantMaze(request);
  }

 private:
  s21::ModelMaze* model_{};
};
}  // namespace s21

#endif  // S21_CONTROLLER_MAZE_H_
