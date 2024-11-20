#ifndef MODEL_S21_MAZE_
#define MODEL_S21_MAZE_
// #include <QDebug>
#include <iostream>
#include <vector>

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
using Cel = short unsigned int;
using WallsVector = std::vector<bool>;
using UnionVector = std::vector<Cel>;
struct Coordinate {
  Cel row{}, col{};
};
using RouteCoordVector = std::vector<Coordinate>;
struct MazeRoute {
  Coordinate start{}, end{};
  std::vector<Coordinate> routes;
};

struct MazeCell {
  bool right_border{};
  bool down_border{};
  Cel mass{};
};

struct MazeSize {
  Cel maze_rows{}, maze_cols{};
};
class ModelMaze;
class InterfaceMaze {
  friend class ModelMaze;

 public:
  virtual bool IsEmpty() const = 0;
  // Walls
  virtual bool IsThereRightWall(Coordinate coord) const = 0;
  virtual bool IsThereBottomWall(Coordinate coord) const = 0;
  virtual void SetRightWall(Coordinate coord, bool right_wal) = 0;
  virtual void SetBottomWall(Coordinate coord, bool bottom_wal) = 0;
  // With rows and cols
  virtual bool IsThereRightWall(Cel rows, Cel cols) const = 0;
  virtual bool IsThereBottomWall(Cel rows, Cel cols) const = 0;
  virtual void SetRightWall(Cel rows, Cel cols, bool right_wal) = 0;
  virtual void SetBottomWall(Cel rows, Cel cols, bool bottom_wal) = 0;
  // Size
  virtual MazeSize Size() const = 0;
  virtual Cel SizeRows() const = 0;
  virtual Cel SizeCols() const = 0;
  virtual void SetSize(MazeSize size) = 0;       // warning, reset data
  virtual void SetSize(Cel rows, Cel cols) = 0;  // warning, reset data
  // To routes
  virtual RouteCoordVector GetRoute() const = 0;
  virtual void AddRoute(RouteCoordVector route) = 0;
  virtual Coordinate GetStart() const = 0;
  virtual Coordinate GetEnd() const = 0;
  // Points of route
  virtual void SetStart(Coordinate start_coords) = 0;
  virtual void SetEnd(Coordinate end_coords) = 0;
  virtual void SetStart(Cel row, Cel col) = 0;
  virtual void SetEnd(Cel row, Cel col) = 0;
  // Union
  virtual Cel GetUnion(Coordinate coord) const = 0;
  virtual void SetUnion(Coordinate coord, Cel uni) = 0;
  // With rows and cols
  virtual Cel GetUnion(Cel row, Cel col) const = 0;
  virtual void SetUnion(Cel row, Cel col, Cel uni) = 0;
  // If have data, need method destructor
  virtual ~InterfaceMaze() = default;
};

class CoolMaze : public InterfaceMaze {
 public:
  bool IsEmpty() const override {
    return right_wall_vector_.empty() || bottom_wall_vector_.empty();
  }
  // Walls
  bool IsThereRightWall(Coordinate coord) const override;
  bool IsThereBottomWall(Coordinate coord) const override;
  void SetRightWall(Coordinate coord, bool wal) override;
  void SetBottomWall(Coordinate coord, bool wal) override;
  // With rows and cols
  bool IsThereRightWall(Cel row, Cel col) const override;
  bool IsThereBottomWall(Cel row, Cel col) const override;
  void SetRightWall(Cel row, Cel col, bool right_wal) override;
  void SetBottomWall(Cel row, Cel col, bool bottom_wal) override;
  // Size
  MazeSize Size() const override;
  Cel SizeRows() const override;
  Cel SizeCols() const override;
  void SetSize(MazeSize size) override;
  void SetSize(Cel rows, Cel cols) override;
  // To routes
  RouteCoordVector GetRoute() const override;
  void AddRoute(RouteCoordVector route) override;
  Coordinate GetStart() const override;
  Coordinate GetEnd() const override;
  // Points of route
  void SetStart(Coordinate start_coords) override;
  void SetEnd(Coordinate end_coords) override;
  void SetStart(Cel row, Cel col) override;
  void SetEnd(Cel row, Cel col) override;
  // Union
  Cel GetUnion(Coordinate coord) const override;
  void SetUnion(Coordinate coord, Cel multitude) override;
  // With rows and cols
  Cel GetUnion(Cel row, Cel col) const override;
  void SetUnion(Cel row, Cel col, Cel uni) override;

 private:
#ifdef TESTS_DEF
 public:
#endif
  std::size_t Cell(Coordinate coord) const {
    return (coord.row * size_.maze_cols) + coord.col;
  }
  WallsVector right_wall_vector_;
  WallsVector bottom_wall_vector_;
  UnionVector cell_union_vector_;
  RouteCoordVector calculated_route_vector_;
  Coordinate start_coord_{};
  Coordinate end_coord_{};
  MazeSize size_{};
};

}  // namespace s21
#endif  // MODEL_S21_MAZE_
