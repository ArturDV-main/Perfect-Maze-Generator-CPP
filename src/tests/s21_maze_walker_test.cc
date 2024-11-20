#include "../model/s21_maze_walker.h"

#include "gtest/gtest.h"
#include "stdio.h"

namespace s21walkertest {
class ModelMaze {
 public:
  ModelMaze() {
    maze = new s21::CoolMaze;
    std::cout << "maze contaner walker" << std::endl;
  }
  s21::CoolMaze *maze;
  ~ModelMaze() { delete maze; }
};
}  // namespace s21walkertest

/*
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1
and the second — the wall at the bottom.
1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1

 __ __ __ __
|__    __   |
|  |   __|  |
|__ __|   __|
|__ __ __ __|
*/

TEST(RouteFinder, RoutTest4x4) {
  s21walkertest::ModelMaze model;
  model.maze->SetSize(4, 4);
  model.maze->SetStart(s21::Coordinate{0, 0});
  EXPECT_EQ(model.maze->GetStart().col, 0);
  EXPECT_EQ(model.maze->GetStart().row, 0);
  model.maze->SetEnd(3, 3);
  EXPECT_EQ(model.maze->GetEnd().col, 3);
  EXPECT_EQ(model.maze->GetEnd().row, 3);
  int right[16] = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1};
  int down[16] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1};
  int i = 0;
  for (s21::Cel row = 0; row < model.maze->Size().maze_rows; row++) {
    for (s21::Cel col = 0; col < model.maze->Size().maze_cols; col++) {
      model.maze->SetRightWall(row, col, right[i]);
      model.maze->SetBottomWall(row, col, down[i]);
      i++;
    }
  }
  s21::MazeWalker w;
  EXPECT_TRUE(w.FindRoute(model.maze));
  s21::RouteCoordVector r = model.maze->GetRoute();
  EXPECT_FALSE(r.empty());
}

TEST(RouteFinder, RoutTestLogic) {
  s21walkertest::ModelMaze model;
  s21::MazeWalker w;
  model.maze->SetSize(4, 4);
  model.maze->SetStart(3, 1);
  model.maze->SetEnd({0, 3});
  int right[16] = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1};
  int down[16] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1};
  int i = 0;
  for (s21::Cel row = 0; row < model.maze->Size().maze_rows; row++) {
    for (s21::Cel col = 0; col < model.maze->Size().maze_cols; col++) {
      model.maze->SetRightWall(row, col, right[i]);
      model.maze->SetBottomWall(row, col, down[i]);
      i++;
    }
  }
  EXPECT_TRUE(w.FindRoute(model.maze));
  int right2[16] = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  int down2[16] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1};
  i = 0;
  for (s21::Cel row = 0; row < model.maze->Size().maze_rows; row++) {
    for (s21::Cel col = 0; col < model.maze->Size().maze_cols; col++) {
      model.maze->SetRightWall(row, col, right2[i]);
      model.maze->SetBottomWall(row, col, down2[i]);
      i++;
    }
  }
  EXPECT_FALSE(w.FindRoute(model.maze));
  int right3[16] = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  int down3[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1};
  i = 0;
  for (s21::Cel row = 0; row < model.maze->Size().maze_rows; row++) {
    for (s21::Cel col = 0; col < model.maze->Size().maze_cols; col++) {
      model.maze->SetRightWall(row, col, right3[i]);
      model.maze->SetBottomWall(row, col, down3[i]);
      i++;
    }
  }
  EXPECT_FALSE(w.FindRoute(model.maze));
}

TEST(RouteFinder, Exeptions) {
  s21walkertest::ModelMaze model;
  s21::MazeWalker w;
  EXPECT_FALSE(w.FindRoute(model.maze));
  model.maze->SetSize(4, 4);
  EXPECT_FALSE(w.FindRoute(model.maze));
  model.maze->SetStart(55, 55);
  model.maze->SetEnd({300, 300});
  EXPECT_FALSE(w.FindRoute(model.maze));
  delete model.maze;
  model.maze = nullptr;
  EXPECT_FALSE(w.FindRoute(model.maze));
}