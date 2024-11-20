#include "s21_maze_generator.h"

bool s21::MazeGenerator::CreatePerfectMaze(MazeGen* maze) {
  if (maze == nullptr) {
    std::cout << "maze ptr null" << std::endl;
    return false;
  }
  if (maze->IsEmpty()) {
    std::cout << "maze is empty" << std::endl;
    return false;
  }
  maze_ = maze;
  lastrow_ = maze_->Size().maze_rows - 1;
  lastcol_ = maze_->Size().maze_cols - 1;
  FillRndBank();
  MassFill();
  FillRow(0);
  for (Cel row = 1; row <= lastrow_; row++) {
    NextRow(row);
    FillRow(row);
  }
  LastRow(lastrow_);
  return true;
}

bool s21::MazeGenerator::GetRandBool() {
  if (rnd_bank_.empty()) {
    FillRndBank();
  }
  bool rnd = rnd_bank_.back();
  rnd_bank_.pop_back();
  return rnd;
}

void s21::MazeGenerator::FillRndBank() {
  Cel iter = maze_->Size().maze_rows * maze_->Size().maze_cols * 3;
  for (Cel i = 0; i < iter; i++) {
    rnd_bank_.push_back(gen_.BoolGenerate());
  }
}

void s21::MazeGenerator::LastRow(Cel row) {
  for (Cel col = 0; col <= lastcol_; col++) {
    SetBootWall(row, col, true);
    if (col == lastcol_) {
      SetRightWall(row, col, true);
    } else if (CellUnion(row, col + 1) != CellUnion(row, col)) {
      SetRightWall(row, col, false);
      CoopMassToRight(row, col);
    }
  }
}

void s21::MazeGenerator::NextRow(Cel row) {
  for (Cel col = 0; col <= lastcol_; col++) {
    if (!WallBootom(row - 1, col)) UnionSet(row, col, CellUnion(row - 1, col));
  }
}

void s21::MazeGenerator::MassFill() {
  for (Cel row = 0; row <= lastrow_; row++)
    for (Cel col = 0; col <= lastcol_; col++) {
      UnionSet(row, col, Mass());
    }
}

void s21::MazeGenerator::FillRow(Cel row) {
  // Right borders
  for (Cel col = 0; col <= lastcol_; col++) {
    if (GetRandBool() == true) {
      SetRightWall(row, col, true);
    } else {
      NotRightWall(row, col);
    }
  }
  // Down borders
  for (Cel col = 0; col <= lastcol_; col++) {
    if (GetRandBool() == true) {
      MakeDownWall(row, col);
    } else {
      SetBootWall(row, col, false);
    }
  }
}

void s21::MazeGenerator::NotRightWall(Cel row, Cel col) {
  if (col == lastcol_) {
    SetRightWall(row, col, true);
    return;
  }
  if (CellUnion(row, col) == CellUnion(row, col + 1)) {
    SetRightWall(row, col, true);
    return;
  }
  SetRightWall(row, col, false);
  CoopMassToRight(row, col);
}

void s21::MazeGenerator::CoopMassToRight(Cel row, Cel col) {
  Cel mass_right = CellUnion(row, col + 1);
  Cel this_mass = CellUnion(row, col);
  for (Cel col = 0; col <= lastcol_; col++) {
    if (CellUnion(row, col) == mass_right) {
      UnionSet(row, col, this_mass);
    }
  }
}

void s21::MazeGenerator::MakeDownWall(Cel row, Cel col) {
  if (PossibleDownBoorder(row, col)) {
    SetBootWall(row, col, true);
  } else {
    SetBootWall(row, col, false);
  }
}

bool s21::MazeGenerator::PossibleDownBoorder(Cel row, Cel col) {
  int count = 0;
  Cel mass = CellUnion(row, col);
  for (Cel i = 0; i <= lastcol_; i++) {
    if (WallBootom(row, i) == false && CellUnion(row, i) == mass) {
      count++;
      if (count > 1) {
        return true;
      }
    }
  }
  return false;
}

s21::BoolGenerator::BoolGenerator() {
  std::mt19937 m(rd());
  mt = m;
  std::bernoulli_distribution d(chance);
  dist = d;
}

bool s21::BoolGenerator::BoolGenerate() { return dist(mt); }
