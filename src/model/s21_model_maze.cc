#include "s21_model_maze.h"

const s21::Maze* s21::ModelMaze::GetMaze() const {
    const s21::Maze* maze_p = &maze_;
    return maze_p; 
}

int s21::ModelMaze::GenerateMaze(int wight, int hight) {
    std::printf("Generated wight: %d, hight: %d", wight, hight);
    return 0; 
}
