#include "scenegl.h"

#include <QPainter>
#include <QTimer>

#include "helpergl.h"

SceneGL::SceneGL(QWidget *parent) : QOpenGLWidget(parent) {
  setFixedSize(500, 500);
  setAutoFillBackground(false);
}

void SceneGL::paintEvent(QPaintEvent *event) {
  if (helper_ == nullptr) {
    return;
  }
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  helper_->paint(&painter, event);
  painter.end();
}

void SceneGL::mousePressEvent(QMouseEvent *event) {
  m_lastPos_ = event->position().toPoint();
  qDebug() << m_lastPos_ << "mouse pressed";

  if (helper_ == nullptr) {
    return;
  }
  if (!helper_->haveMaze()) {
    return;
  }
  if (first_position_flag_) {
    helper_->m_pos_b = m_lastPos_;
    first_position_flag_ = false;
  } else {
    helper_->m_pos_a = m_lastPos_;
    first_position_flag_ = true;
  }
  update();
}
