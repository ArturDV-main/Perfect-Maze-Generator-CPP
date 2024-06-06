#include "s21_model_perceptron.h"

std::vector<std::vector<unsigned char>> ParseCsv(const std::string& filename,
                                                 size_t image_resolution) {
  std::vector<std::vector<unsigned char>> data;
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("file");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string token;
    std::vector<unsigned char> image;
    // Чтение метки
    std::getline(iss, token, ',');
    image.push_back(std::stoi(token));
    if (image[lable] > 28) {
      throw std::runtime_error("lable token");
    }
    // Чтение пикселей
    while (std::getline(iss, token, ',')) {
      image.push_back(255 - std::stoi(token));
    }
    if (image.size() == image_resolution + pixel) data.push_back(image);
  }
  return data;
}
