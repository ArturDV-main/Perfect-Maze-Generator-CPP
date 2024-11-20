#ifndef MODEL_S21_MODEL_MAZE_
#define MODEL_S21_MODEL_MAZE_
// #include <QDebug>

#include "s21_maze.h"
#include "s21_maze_generator.h"
#include "s21_maze_loader_saver.h"
#include "s21_maze_walker.h"
// #include "s21_test_maze.h"
namespace s21

{
using Maze = CoolMaze;
class ModelMaze {
 public:
  struct MazeRequest {
    enum Option { Generate, OpenFile, SaveFile, FindRoute, GenerateTest };
    Option opt_ion;
    std::string file_name;
    MazeSize size;
    Coordinate A_coord, B_coord;
  } req;

  ModelMaze(){};
  ~ModelMaze() {
    if (maze_ != nullptr) delete maze_;
  };
  Maze* GetMaze();
  bool WantMaze(MazeRequest request);

 private:
  bool SaveMaze(MazeRequest& request);

  bool OpenMaze(MazeRequest& request);

  bool GenerateNewMaze(MazeRequest& request);
  void AddStartEndPoints(Coordinate A_coord, Coordinate B_coord);
  bool GenerateRoute(MazeRequest& request);
  Maze* maze_{};
  bool InitMaze(short unsigned int rows, short unsigned int cols);
};  // class ModelMaze

}  // namespace s21

#endif  // MODEL_S21_MODEL_MAZE_
