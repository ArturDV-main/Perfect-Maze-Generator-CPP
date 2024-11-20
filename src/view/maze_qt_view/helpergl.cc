#include "helpergl.h"

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <cmath>
#include <vector>

#include "./media/image_a_data.cc"
#include "./media/image_b_data.cc"

Helper::Helper() {
  QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
  gradient.setColorAt(0.0, Qt::white);
  background_ = QBrush(QColor(200, 200, 200));
  pngLoader();
  m_pos_a = {100550, 100550};
  m_pos_b = {100550, 100550};
}

void Helper::pngLoader() {
  QByteArray byteArray_a_png(reinterpret_cast<const char *>(a_png), a_png_len);
  QByteArray byteArray_b_png(reinterpret_cast<const char *>(b_png), b_png_len);
  QImage a_png_file;
  a_png_file.loadFromData(byteArray_a_png, "PNG");
  a_pixmap_ = QPixmap::fromImage(a_png_file);
  QImage b_png_file;
  b_png_file.loadFromData(byteArray_b_png, "PNG");
  b_pixmap_ = QPixmap::fromImage(b_png_file);
}

void Helper::paint(QPainter *painter, QPaintEvent *event) {
  painter->fillRect(event->rect(), background_);
  painter->translate(midle_x_, midle_y_);
  painter->setPen(QPen(Qt::black, line_width_));
  paintMap(painter);
  paintMaze(painter);
  paintMazeRoute(painter);
  paintStartStopPos(painter);
}

void Helper::paintMazeRoute(QPainter *painter) {
  if (maze_ptr_ == nullptr) {
    qDebug() << "maze null";
    return;
  }
  painter->save();
  if (maze_ptr_->GetRoute().size() < 1) {
    qDebug() << "maze route suck";
    return;
  }
  painter->setPen(QPen(Qt::red, line_width_));
  s21::Coordinate start = maze_ptr_->GetStart();
  s21::Coordinate end = maze_ptr_->GetEnd();
  s21::Coordinate walker = start;
  for (short unsigned int i = 0; i < maze_ptr_->GetRoute().size(); i++) {
    QPointF walker_pos_a(walker.col * lineLength_x_ + lineLength_x_ / 2,
                         walker.row * lineLength_y_ + lineLength_y_ / 2);
    walker = maze_ptr_->GetRoute().at(i);
    QPointF walker_pos_b(walker.col * lineLength_x_ + lineLength_x_ / 2,
                         walker.row * lineLength_y_ + lineLength_y_ / 2);
    painter->drawLine(walker_pos_a, walker_pos_b);
  }
  QPointF walker_pos_a(walker.col * lineLength_x_ + lineLength_x_ / 2,
                       walker.row * lineLength_y_ + lineLength_y_ / 2);
  walker = end;
  QPointF walker_pos_b(end.col * lineLength_x_ + lineLength_x_ / 2,
                       end.row * lineLength_y_ + lineLength_y_ / 2);
  painter->drawLine(walker_pos_a, walker_pos_b);
  painter->restore();
}

void Helper::paintMaze(QPainter *painter) {
  if (maze_ptr_ == nullptr) {
    qDebug() << "maze null";
    return;
  }
  qDebug() << "paint start";
  lineLength_x_ = ((viewport_ - line_width_) / maze_ptr_->Size().maze_cols) /
                  devicePixelRatio;
  lineLength_y_ = ((viewport_ - line_width_) / maze_ptr_->Size().maze_rows) /
                  devicePixelRatio;
  qreal x_1 = line_width_ / 2.0;
  qreal y_1 = line_width_ / 2.0;
  for (short unsigned int i = 0; i < maze_ptr_->Size().maze_rows; i++) {
    for (short unsigned int j = 0; j < maze_ptr_->Size().maze_cols; j++) {
      if (maze_ptr_->IsThereRightWall(i, j) &&
          j != maze_ptr_->Size().maze_cols - 1) {
        //                qDebug()<<"cell" << i << cell->right_border << j;
        painter->drawLine(x_1 + j * lineLength_x_ + lineLength_x_,
                          y_1 + i * lineLength_y_,
                          x_1 + j * lineLength_x_ + lineLength_x_,
                          y_1 + i * lineLength_y_ + lineLength_y_);
      }
      if (maze_ptr_->IsThereBottomWall(i, j) &&
          i != maze_ptr_->Size().maze_rows - 1) {
        //                qDebug()<<"cell" << i << cell->down_border << j;
        painter->drawLine(x_1 + j * lineLength_x_,
                          y_1 + i * lineLength_y_ + lineLength_y_,
                          x_1 + j * lineLength_x_ + lineLength_x_,
                          y_1 + i * lineLength_y_ + lineLength_y_);
      }
    }
  }
  qDebug() << "paint";
}

void Helper::paintMap(QPainter *painter) {
  qreal lineLength_ = (viewport_ - line_width_ / 2) / devicePixelRatio;
  qreal coordinate = line_width_ / 2;
  painter->drawLine(coordinate, coordinate, lineLength_, coordinate);
  painter->drawLine(coordinate, coordinate, coordinate, lineLength_);
  painter->drawLine(coordinate, lineLength_, lineLength_, lineLength_);
  painter->drawLine(lineLength_, coordinate, lineLength_, lineLength_);
}

void Helper::paintStartStopPos(QPainter *painter) {
  if (maze_ptr_ == nullptr) {
    qDebug() << "maze null";
    return;
  }
  painter->save();
  QPixmap scaledPixmap =
      a_pixmap_.scaled(lineLength_x_ * 0.8, lineLength_y_ * 0.8,
                       Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  if (m_pos_a.rx() != 0) {
    QPointF a(std::floor(m_pos_a.rx() / lineLength_x_) * lineLength_x_ +
                  lineLength_x_ * 0.1,
              std::floor(m_pos_a.ry() / lineLength_y_) * lineLength_y_ +
                  lineLength_y_ * 0.1);
    painter->drawPixmap(a, scaledPixmap);
  }
  if (m_pos_b.rx() != 0) {
    QPointF b(std::floor(m_pos_b.rx() / lineLength_x_) * lineLength_x_ +
                  lineLength_x_ * 0.1,
              std::floor(m_pos_b.ry() / lineLength_y_) * lineLength_y_ +
                  lineLength_y_ * 0.1);
    scaledPixmap =
        b_pixmap_.scaled(lineLength_x_ * 0.8, lineLength_y_ * 0.8,
                         Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(b, scaledPixmap);
  }
  painter->restore();
}
