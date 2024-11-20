#ifndef MODEL_S21_MAZE_WALKER_H_
#define MODEL_S21_MAZE_WALKER_H_
#include <stack>
#include <string>

#include "s21_maze.h"

/*
The maze can be stored in a file as a number of rows and columns,
as well as two matrices containing the positions of vertical and horizontal
walls respectively. The first matrix shows the wall to the right of each cell,
and the second - the wall at the bottom.

4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
*/

namespace s21 {
using CoordStack = std::vector<Coordinate>;
using MazeWalk = InterfaceMaze;
class MazeWalker {
 public:
  bool FindRoute(MazeWalk *maze);

 protected:
  bool BuildPerfectMazeRoute();
  bool InFinish();
  void ToUnion(Coordinate coord, Cel uni) { maze_->SetUnion(coord, uni); }
  void MassFill();
  void MakeCellVisited(Coordinate coord) { maze_->SetUnion(coord, 1); }
  bool IsCellNotVisited(Coordinate coord) {
    return maze_->GetUnion(coord) == 0;
  }
  void RecordStep() { route_.push_back(walker_); }
  bool TakeStep();
  CoordStack HaveNeighbours();
  void Up(CoordStack &neighbours);
  void Down(CoordStack &neighbours);
  void Left(CoordStack &neighbours);
  void Right(CoordStack &neighbours);
  bool RightWall(Coordinate coord) {
    return maze_->IsThereRightWall(coord);
    ;
  }
  bool BottomWall(Coordinate coord) { return maze_->IsThereBottomWall(coord); }
  void Init(MazeWalk *maze) {
    maze_ = maze;
    lastrow_ = maze_->SizeRows() - 1;
    lastcol_ = maze_->SizeCols() - 1;
    start_ = maze_->GetStart();
    end_ = maze_->GetEnd();
    RouteClear();
  }
  void RouteClear() {
    stack_.clear();
    route_.clear();
    maze_->AddRoute(stack_);
  }
  // Variables
  CoordStack stack_;
  CoordStack route_;
  MazeWalk *maze_;
  Coordinate start_{};
  Coordinate end_{};
  Coordinate walker_{};
  int max_iterations_ = 1500000;
  int test_maze_variant_ = 0;
  Cel lastrow_{}, lastcol_{};
};
}  // namespace s21
#endif  // MODEL_S21_MAZE_WALKER_H_