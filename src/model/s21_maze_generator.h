#ifndef MODEL_S21_MAZE_GENERATOR_H_
#define MODEL_S21_MAZE_GENERATOR_H_
#include <array>
#include <random>
// #include <QDebug>

#include "s21_maze.h"

namespace s21 {
using MazeGen = InterfaceMaze;
class BoolGenerator {
 public:
  BoolGenerator();
  bool BoolGenerate();

 private:
  std::mt19937 mt;
  // this is the chance of getting true,
  const double chance = 0.4;  // between 0 and 1;
  std::bernoulli_distribution dist;
  std::random_device rd;

};  // class BoolGenerotor

class MazeGenerator {
 public:
  MazeGenerator(){};
  bool CreatePerfectMaze(MazeGen* maze);

 protected:
#ifdef TESTS_DEF
 public:
#endif
  bool WallBootom(Cel row, Cel col) {
    return maze_->IsThereBottomWall(row, col);
  }
  void SetBootWall(Cel row, Cel col, bool wall) {
    maze_->SetBottomWall(row, col, wall);
  }
  bool WallRight(Cel row, Cel col) { return maze_->IsThereRightWall(row, col); }
  void SetRightWall(Cel row, Cel col, bool wall) {
    maze_->SetRightWall(row, col, wall);
  }
  Cel CellUnion(Cel row, Cel col) {
    { return maze_->GetUnion(row, col); }
  }
  void UnionSet(Cel row, Cel col, Cel un) { maze_->SetUnion(row, col, un); }
  bool GetRandBool();
  void FillRndBank();
  void LastRow(Cel row);
  void NextRow(Cel row);
  void FillRow(Cel row);
  void NotRightWall(Cel row, Cel column);
  void CoopMassToRight(Cel row, Cel col);
  void MakeDownWall(Cel row, Cel col);
  bool PossibleDownBoorder(Cel row, Cel column);
  void MassFill();
  Cel Mass() {
    if (mass_ == 2600) {
      mass_ = 0;
    }
    return mass_++;
  }
  Cel mass_{}, lastrow_{}, lastcol_{};
  MazeGen* maze_{};
  BoolGenerator gen_;
  std::vector<bool> rnd_bank_;
};

}  // namespace s21
#endif  // MODEL_S21_MAZE_GENERATOR_H_
