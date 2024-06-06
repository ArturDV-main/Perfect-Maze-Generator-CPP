#ifndef S21_FACADE_mazeE_
#define S21_FACADE_mazeE_

#include <string>

#include "./s21_model_maze.h"

namespace s21 {
class FacadePerceptron {
 public:
  FacadePerceptron() = default;
  FacadePerceptron(const FacadePerceptron&) = delete;
  FacadePerceptron(FacadePerceptron&&) = delete;
  ~FacadePerceptron() = default;
  FacadePerceptron& operator=(const FacadePerceptron&) = delete;
  FacadePerceptron& operator=(FacadePerceptron&&) = delete;
  bool IsAllGood() { return true; }
  void OpenCsv(std::string file_name, size_t image_resolution) {
    csv_vector_ = ParseCsv(file_name, image_resolution);
  }
  const std::vector<std::vector<unsigned char>>* GetCsv() {
    const std::vector<std::vector<unsigned char>>* tmp = &csv_vector_;
    return tmp;
  }

 private:
  std::vector<std::vector<unsigned char>> csv_vector_;
};
}  // namespace s21

#endif  // S21_FACADE_mazeE_
