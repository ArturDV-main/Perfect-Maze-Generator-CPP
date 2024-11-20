#include "s21_model_maze.h"

s21::Maze *s21::ModelMaze::GetMaze() {
  s21::Maze *maze_p = maze_;
  return maze_p;
}

bool s21::ModelMaze::WantMaze(MazeRequest request) {
  switch (request.opt_ion) {
    case MazeRequest::SaveFile:
      SaveMaze(request);
      break;
    case MazeRequest::FindRoute:
      GenerateRoute(request);
      break;
    case MazeRequest::OpenFile:
      OpenMaze(request);
      break;
    case MazeRequest::Generate:
      GenerateNewMaze(request);
      break;
    default:
      if (!InitMaze(request.size.maze_rows, request.size.maze_cols)) {
        // qDebug() << "maze memory low";
        return false;
      }
      // TestMaze::BuildTestMaze(maze_);
      break;
  }
  return true;
}

bool s21::ModelMaze::SaveMaze(MazeRequest &request) {
  return LoaderSaverMaze::SaveMaze(maze_, request.file_name);
}

bool s21::ModelMaze::OpenMaze(MazeRequest &request) {
  if (!InitMaze(request.size.maze_rows, request.size.maze_cols)) {
    // qDebug() << "maze memory low";
    return false;
  }
  return LoaderSaverMaze::LoadMaze(maze_, request.file_name);
}

bool s21::ModelMaze::GenerateNewMaze(MazeRequest &request) {
  if (!InitMaze(request.size.maze_rows, request.size.maze_cols)) {
    // qDebug() << "maze memory low";
    return false;
  }
  MazeGenerator generator;
  maze_->SetSize(MazeSize{request.size.maze_rows, request.size.maze_cols});
  generator.CreatePerfectMaze(maze_);
  return true;
}

void s21::ModelMaze::AddStartEndPoints(Coordinate A_coord, Coordinate B_coord) {
  maze_->SetStart(A_coord);
  maze_->SetEnd(B_coord);
}

bool s21::ModelMaze::GenerateRoute(MazeRequest &request) {
  AddStartEndPoints(request.A_coord, request.B_coord);
  MazeWalker w;
  w.FindRoute(maze_);
  return true;
}

bool s21::ModelMaze::InitMaze(short unsigned int rows,
                              short unsigned int cols) {
  if (maze_ != nullptr) {
    delete maze_;
  }
  maze_ = new Maze();
  maze_->SetSize(rows, cols);
  if (maze_ == nullptr) {
    std::cout << "maze memory low" << std::endl;
    // qDebug() << "maze memory low";
    return false;
  }
  return true;
}
