#include "../model/s21_model_maze.h"
#include "gtest/gtest.h"
#include "stdio.h"

std::string file_name_ = TESTS_OBJ_PATH;

TEST(LoaderSaverTest1, LaodTest1) {
  s21::ModelMaze model;
  s21::ModelMaze::MazeRequest r;
  r.file_name = file_name_ + "maze1.mz";
  r.opt_ion = s21::ModelMaze::MazeRequest::OpenFile;
  model.WantMaze(r);
  r.opt_ion = s21::ModelMaze::MazeRequest::SaveFile;
  r.file_name = file_name_ + "maze5.mz";
  model.WantMaze(r);
  EXPECT_EQ(432, 432);
}
