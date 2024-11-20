#define TESTS_DEF
#include "../model/s21_maze_generator.h"

#include "gtest/gtest.h"
#include "stdio.h"

namespace s21gentest {
class ModelMaze {
 public:
  ModelMaze() {
    maze = new s21::CoolMaze;
    std::cout << "maze contaner walker" << std::endl;
  }
  s21::CoolMaze *maze;
  ~ModelMaze() { delete maze; }
};
}  // namespace s21gentest

TEST(Generator, GenTest1) {
  s21gentest::ModelMaze model;
  s21::MazeGenerator generator;
  model.maze->SetSize(4, 4);
  EXPECT_EQ(model.maze->Size().maze_cols, 4);
  EXPECT_EQ(model.maze->Size().maze_rows, 4);
  model.maze->SetSize(s21::MazeSize{4, 4});
  generator.CreatePerfectMaze(model.maze);
  generator.MassFill();
  EXPECT_TRUE(model.maze->GetUnion(1, 1) != 0);
  generator.UnionSet(1, 1, 1);
  EXPECT_EQ(model.maze->GetUnion(1, 1), 1);
}

TEST(Generator, GenTest2) {
  s21gentest::ModelMaze model;
  s21::MazeGenerator generator;
  model.maze->SetSize(4, 4);
  generator.CreatePerfectMaze(model.maze);
  generator.SetBootWall(1, 1, true);
  EXPECT_TRUE(generator.WallBootom(1, 1));
  model.maze->SetBottomWall(2, 2, true);
  EXPECT_TRUE(generator.WallBootom(2, 2));
  generator.SetRightWall(1, 1, true);
  EXPECT_TRUE(generator.WallRight(1, 1));
}

TEST(Generator, GenExeption) {
  s21gentest::ModelMaze model;
  s21::MazeGenerator generator;
  EXPECT_FALSE(generator.CreatePerfectMaze(model.maze));
  delete model.maze;
  model.maze = nullptr;
  EXPECT_FALSE(generator.CreatePerfectMaze(model.maze));
}
