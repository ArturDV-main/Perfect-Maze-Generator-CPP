#ifndef MODEL_S21_MODEL_MAZE_
#define MODEL_S21_MODEL_MAZE_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21
{

class ModelMaze {
  public:
    int GetMaze();
    int GenerateMaze(int wight, int hight);
};

} // namespace s21

#endif  // MODEL_S21_MODEL_MAZE_
