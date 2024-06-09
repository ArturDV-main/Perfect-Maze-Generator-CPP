#ifndef MODEL_S21_MODEL_MAZE_
#define MODEL_S21_MODEL_MAZE_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21
{

  struct Maze{
    int height, weight;
    double *maze;
  };

class ModelMaze {
  public:
    const Maze* GetMaze() const;
    int GenerateMaze(int wight, int hight);
  private:
    Maze maze_;
};

} // namespace s21

#endif  // MODEL_S21_MODEL_MAZE_
