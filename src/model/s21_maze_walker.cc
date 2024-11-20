#include "s21_maze_walker.h"

#include <iostream>
#include <stack>

namespace s21 {

bool s21::MazeWalker::FindRoute(MazeWalk *maze) {
  if (maze == nullptr) {
    std::cout << "maze ptr null" << std::endl;
    return false;
  }
  Init(maze);
  if (maze->IsEmpty()) {
    std::cout << "maze is empty" << std::endl;
    return false;
  }
  if (start_.row > lastrow_ || start_.col > lastcol_ || end_.row > lastrow_ ||
      end_.col > lastcol_) {
    std::cout << "no start or end" << std::endl;
    return false;
  }
  if (end_.row == start_.row && end_.col == start_.col) {
    std::cout << "start on end" << std::endl;
    return false;
  }

  bool b = BuildPerfectMazeRoute();
  if (b) {
    maze_->AddRoute(stack_);
  }
  return b;
}

bool MazeWalker::BuildPerfectMazeRoute() {
  MassFill();
  walker_ = start_;
  MakeCellVisited(walker_);
  int iter = 0;
  while (!InFinish()) {
    RecordStep();
    if (iter > max_iterations_) {
      std::cout << "iter limit" << std::endl;
      return false;
    }
    iter++;
    if (!TakeStep()) {
      std::cout << "no any steps" << std::endl;
      return false;
    }
  }
  route_.push_back(walker_);
  return true;
}

bool MazeWalker::TakeStep() {
  CoordStack neighbours = HaveNeighbours();
  if (!neighbours.empty()) {
    stack_.push_back(walker_);
    walker_ = neighbours.back();
    MakeCellVisited(walker_);
  } else if (!stack_.empty()) {
    walker_ = stack_.back();
    stack_.pop_back();
    return true;
  } else {
    std::cout << "no neighbours and stack empty" << std::endl;
    return false;
  }
  return true;
}

CoordStack MazeWalker::HaveNeighbours() {
  CoordStack neighbours;
  Up(neighbours);
  Down(neighbours);
  Left(neighbours);
  Right(neighbours);
  return neighbours;
}

void MazeWalker::Up(CoordStack &neighbours) {
  if (walker_.row == 0) {
    return;
  }
  Coordinate up_cell = walker_;
  up_cell.row -= 1;
  if (IsCellNotVisited(up_cell) && !BottomWall(up_cell)) {
    neighbours.push_back(up_cell);
  }
}

void MazeWalker::Down(CoordStack &neighbours) {
  if (walker_.row == lastrow_) {
    return;
  }
  Coordinate down_cell = walker_;
  down_cell.row += 1;
  if (IsCellNotVisited(down_cell) && !BottomWall(walker_)) {
    neighbours.push_back(down_cell);
  }
}

void MazeWalker::Left(CoordStack &neighbours) {
  if (walker_.col == 0) {
    return;
  }
  Coordinate left_cell = walker_;
  left_cell.col -= 1;
  if (IsCellNotVisited(left_cell) && !RightWall(left_cell)) {
    neighbours.push_back(left_cell);
  }
}

void MazeWalker::Right(CoordStack &neighbours) {
  if (walker_.col == lastcol_) {
    return;
  }
  Coordinate right_cell = walker_;
  right_cell.col += 1;
  if (IsCellNotVisited(right_cell) && !RightWall(walker_)) {
    neighbours.push_back(right_cell);
  }
}

bool MazeWalker::InFinish() {
  return walker_.row == end_.row && walker_.col == end_.col;
}

void MazeWalker::MassFill() {
  for (Cel row = 0; row <= lastrow_; row++) {
    for (Cel col = 0; col <= lastcol_; col++) {
      ToUnion(Coordinate{row, col}, Cel{0});
    }
  }
}
}  // namespace s21
