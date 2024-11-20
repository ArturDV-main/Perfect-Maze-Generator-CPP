#include "../model/s21_maze_loader_saver.h"

#include "gtest/gtest.h"
#include "stdio.h"

std::string file_name_ = TESTS_OBJ_PATH;

class s21::ModelMaze {
 public:
  ModelMaze() { maze = new CoolMaze(); }
  s21::CoolMaze *maze;
};

TEST(LoaderSaverTest1, LaodTest1) {
  s21::ModelMaze model;
  bool a = s21::LoaderSaverMaze::LoadMaze(model.maze, file_name_ + "maze1.mz");
  std::cout << a << std::endl;
  for (size_t row = 0; row < model.maze->Size().maze_rows; row++) {
    for (size_t col = 0; col < model.maze->Size().maze_cols; col++) {
      std::cout << model.maze->IsThereRightWall(row, col) << " ";
    }
  }
  for (size_t row = 0; row < model.maze->Size().maze_rows; row++) {
    for (size_t col = 0; col < model.maze->Size().maze_cols; col++) {
      std::cout << model.maze->IsThereBottomWall(row, col) << " ";
    }
  }
  EXPECT_EQ(432, 432);
}

TEST(LoaderSaverTest2, SaveTest1) {
  s21::ModelMaze model;
  bool a = s21::LoaderSaverMaze::LoadMaze(model.maze, file_name_ + "maze1.mz");
  std::cout << a << std::endl;
  bool b = s21::LoaderSaverMaze::SaveMaze(model.maze, file_name_ + "maze3.mz");
  std::cout << b << std::endl;
  EXPECT_EQ(432, 432);
}