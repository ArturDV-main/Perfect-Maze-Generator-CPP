#include "s21_maze.h"

namespace s21 {

// Cool maze

bool CoolMaze::IsThereRightWall(Coordinate coord) const {
  return right_wall_vector_.at(Cell(coord));
}

bool CoolMaze::IsThereBottomWall(Coordinate coord) const {
  return bottom_wall_vector_.at(Cell(coord));
}

void CoolMaze::SetRightWall(Coordinate coord, bool wal) {
  right_wall_vector_.at(Cell(coord)) = wal;
}

void CoolMaze::SetBottomWall(Coordinate coord, bool wal) {
  bottom_wall_vector_.at(Cell(coord)) = wal;
}

bool CoolMaze::IsThereRightWall(Cel row, Cel col) const {
  return IsThereRightWall(Coordinate{row, col});
}

bool CoolMaze::IsThereBottomWall(Cel row, Cel col) const {
  return IsThereBottomWall(Coordinate{row, col});
}

void CoolMaze::SetRightWall(Cel row, Cel col, bool right_wal) {
  SetRightWall(Coordinate{row, col}, right_wal);
}

void CoolMaze::SetBottomWall(Cel row, Cel col, bool bottom_wal) {
  SetBottomWall(Coordinate{row, col}, bottom_wal);
}

Cel CoolMaze::GetUnion(Coordinate coord) const {
  return cell_union_vector_.at(Cell(coord));
}

void CoolMaze::SetUnion(Coordinate coord, Cel uni) {
  cell_union_vector_.at(Cell(coord)) = uni;
}

Cel CoolMaze::GetUnion(Cel row, Cel col) const {
  return GetUnion(Coordinate{row, col});
}

void CoolMaze::SetUnion(Cel row, Cel col, Cel uni) {
  SetUnion(Coordinate{row, col}, uni);
}

MazeSize CoolMaze::Size() const {
  const MazeSize size = this->size_;
  return size;
}

Cel CoolMaze::SizeRows() const { return Size().maze_rows; }

Cel CoolMaze::SizeCols() const { return Size().maze_cols; }

void CoolMaze::SetSize(MazeSize size) {
  SetSize(size.maze_rows, size.maze_cols);
}

void CoolMaze::SetSize(Cel rows, Cel cols) {
  right_wall_vector_ = WallsVector(rows * cols, false);
  bottom_wall_vector_ = WallsVector(rows * cols, false);
  cell_union_vector_ = UnionVector(rows * cols, Cel{0});
  size_ = MazeSize{rows, cols};
}

RouteCoordVector CoolMaze::GetRoute() const { return calculated_route_vector_; }

void CoolMaze::AddRoute(RouteCoordVector route) {
  calculated_route_vector_ = route;
}

Coordinate CoolMaze::GetStart() const { return start_coord_; }

Coordinate CoolMaze::GetEnd() const { return end_coord_; }

void CoolMaze::SetStart(Coordinate start_coord) { start_coord_ = start_coord; }

void CoolMaze::SetEnd(Coordinate end_coord) { end_coord_ = end_coord; }

void CoolMaze::SetStart(Cel row, Cel col) {
  start_coord_ = Coordinate{row, col};
}

void CoolMaze::SetEnd(Cel row, Cel col) { end_coord_ = Coordinate{row, col}; }
}  // namespace s21
