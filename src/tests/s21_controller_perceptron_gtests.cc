#include "../controller/s21_controller_perceptron.h"
#include "gtest/gtest.h"

std::string file_name_ = TESTS_OBJ_PATH;

TEST(ControllerPereceptron, SetModel) {
  s21::ControllerPerceptron controller_perceptron;
  s21::FacadePerceptron facade_perceptron;
  controller_perceptron.SetModel(&facade_perceptron);
  EXPECT_EQ(432, 432);
}

TEST(ControllerPereceptron, Train) {
  s21::ControllerPerceptron controller_perceptron;
  s21::FacadePerceptron facade_perceptron;
  controller_perceptron.SetModel(&facade_perceptron);

  // facade_perceptron.OpenCsv(file_name + "my.csv");
  controller_perceptron.OpenCsv(file_name_ + "emnist-letters-test.csv", 784);
  // facade_perceptron.OpenCsv(file_name + "emnist-letters-train.csv");

  auto tmp = controller_perceptron.GetCsv();

  EXPECT_EQ(tmp->size(), 14800);
}
