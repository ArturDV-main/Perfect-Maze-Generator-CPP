#include "s21_maze_loader_saver.h"

#include <fstream>
#include <iostream>

namespace s21 {

bool s21::LoaderSaverMaze::LoadMaze(MazeLoa* maze, std::string f) {
  if (maze == nullptr) {
    return false;
  }

  std::string line;
  std::ifstream in(f);  // окрываем файл для чтения
  if (!in.is_open()) {
    std::cout << "Open file fail" << std::endl;
    // qDebug() << "Open file fail";
    return false;
  }
  size_t row_s, col_s;
  in >> row_s >> col_s;
  if (row_s > 50 || col_s > 50 || row_s == 0 || col_s == 0) {
    std::cout << "maze size in file error" << std::endl;
    // qDebug() << "maze size in file error";
    return false;
  }
  maze->SetSize(row_s, col_s);
  bool wall_tmp{};
  for (size_t row = 0; row < row_s; row++) {
    for (size_t col = 0; col < col_s; col++) {
      in >> wall_tmp;
      maze->SetRightWall(row, col, wall_tmp);
    }
  }
  for (size_t row = 0; row < row_s; row++) {
    for (size_t col = 0; col < col_s; col++) {
      in >> wall_tmp;
      maze->SetBottomWall(row, col, wall_tmp);
    }
  }
  in.close();
  return true;
}

bool LoaderSaverMaze::SaveMaze(MazeLoa* maze, std::string file) {
  if (maze == nullptr) {
    return false;
  }
  std::ofstream out;
  out.open(file);

  if (!out.is_open()) {
    std::cout << "File write error" << std::endl;
    return false;
  }
  out << maze->Size().maze_rows << " " << maze->Size().maze_cols << std::endl;
  for (size_t row = 0; row < maze->Size().maze_rows; row++) {
    for (size_t col = 0; col < maze->Size().maze_cols; col++) {
      out << maze->IsThereRightWall(row, col);
      size_t last = maze->Size().maze_cols - 1;
      if (col < last) {
        out << " ";
      }
    }
    out << std::endl;
  }
  out << std::endl;
  for (size_t row = 0; row < maze->Size().maze_rows; row++) {
    for (size_t col = 0; col < maze->Size().maze_cols; col++) {
      out << maze->IsThereBottomWall(row, col);
      size_t last = maze->Size().maze_cols - 1;
      if (col < last) {
        out << " ";
      }
    }
    out << std::endl;
  }
  out.close();
  std::cout << "File has been written" << std::endl;
  return true;
}

}  // namespace s21
