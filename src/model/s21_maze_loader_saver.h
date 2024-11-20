#ifndef MODEL_S21_MAZE_LOADER_SAVER_H_
#define MODEL_S21_MAZE_LOADER_SAVER_H_
#include <string>

#include "s21_maze.h"

/*
The maze can be stored in a file as a number of rows and columns,
as well as two matrices containing the positions of vertical and horizontal
walls respectively. The first matrix shows the wall to the right of each cell,
and the second - the wall at the bottom.

4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
*/

namespace s21 {
using MazeLoa = InterfaceMaze;
class LoaderSaverMaze {
 public:
  static bool LoadMaze(MazeLoa* maze, std::string file);
  static bool SaveMaze(MazeLoa* maze, std::string file);

 private:
  static inline int test_maze_variant = 0;
};
}  // namespace s21
#endif  // MODEL_S21_MAZE_LOADER_SAVER_H_
