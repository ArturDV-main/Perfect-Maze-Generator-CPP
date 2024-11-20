#ifndef SCENEGL_H_
#define SCENEGL_H_

#include <QMouseEvent>
#include <QOpenGLWidget>

class Helper;

class SceneGL : public QOpenGLWidget {
  Q_OBJECT

 public:
  SceneGL(QWidget *parent = nullptr);
  void SetHelper(Helper *inHelper) { helper_ = inHelper; };

 public slots:

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  bool first_position_flag_{};
  QPoint m_lastPos_;
  Helper *helper_;
};

#endif  // SCENEGL_H_
