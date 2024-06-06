#include "../controller/s21_controller_maze.h"
#include "gtest/gtest.h"

std::string file_name_ = TESTS_OBJ_PATH;

TEST(ControllerPereceptron, SetModel) {
  s21::ControllerPerceptron controller_maze;
  s21::FacadePerceptron facade_maze;
  controller_maze.SetModel(&facade_maze);
  EXPECT_EQ(432, 432);
}

TEST(ControllerPereceptron, Train) {
  s21::ControllerPerceptron controller_maze;
  s21::FacadePerceptron facade_maze;
  controller_maze.SetModel(&facade_maze);

  // facade_maze.OpenCsv(file_name + "my.csv");
  controller_maze.OpenCsv(file_name_ + "emnist-letters-test.csv", 784);
  // facade_maze.OpenCsv(file_name + "emnist-letters-train.csv");

  auto tmp = controller_maze.GetCsv();

  EXPECT_EQ(tmp->size(), 14800);
}
