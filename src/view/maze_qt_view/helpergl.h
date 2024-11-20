#ifndef HELPERGL_H_
#define HELPERGL_H_

#include <QBrush>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QFont>
#include <QPen>
#include <QStaticText>
#include <QWidget>

#include "../../model/s21_maze.h"

class Helper {
  using Maze = s21::InterfaceMaze;

 public:
  Helper();

 public:
  bool haveMaze() { return maze_ptr_ != nullptr; }
  void paint(QPainter *painter, QPaintEvent *event);
  void SetMaze(Maze *maze) {
    maze_ptr_ = maze;
    if (maze_ptr_ == nullptr) {
      qDebug() << "maze_ptr_ null";
      return;
    }
  }
  QPoint m_pos_a{};
  QPoint m_pos_b{};
  qreal lineLength_x_{}, lineLength_y_{};

 private:
  QPixmap a_pixmap_, b_pixmap_;
  Maze *maze_ptr_{};
  const qreal midle_x_ = 0, midle_y_ = 0, viewport_ = 500, line_width_ = 2,
              devicePixelRatio = 1.0;
  QBrush background_;
  void paintMap(QPainter *painter);
  void paintMazeRoute(QPainter *painter);
  void paintMaze(QPainter *painter);
  void paintStartStopPos(QPainter *painter);
  void pngLoader();
};

#endif  // HELPERGL_H_
