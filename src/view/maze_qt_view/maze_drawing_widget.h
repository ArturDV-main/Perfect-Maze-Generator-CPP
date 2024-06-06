#ifndef DRAWINGWIDGET_H_
#define DRAWINGWIDGET_H_

#include <QtWidgets>

class DrawingWidget : public QWidget {
 public:
  DrawingWidget(QWidget *parent = nullptr) : QWidget(parent) {
    parent_ = parent;
    setFixedSize(280, 280);  // Устанавливаем размер виджета 280 x 280 пикселей
    drawing = false;

    // Создаем изображение размером 28 x 28 пикселей
    image = QImage(280, 280, QImage::Format_RGB32);
    image.fill(Qt::white);
  }

  void Reset() {
    image.fill(Qt::white);
    update();
  }

  QImage GetImage() { return image; }

 protected:
  void mousePressEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      lastPoint = event->pos();
      drawing = true;
    }
  }

  void mouseMoveEvent(QMouseEvent *event) override {
    if (event->buttons() & Qt::LeftButton && drawing) {
      QPainter painter(&image);
      QPen pen(Qt::black, 16, Qt::SolidLine, Qt::RoundCap);
      painter.setPen(pen);
      painter.setRenderHint(QPainter::Antialiasing, true);
      painter.drawLine(
          lastPoint,
          event->pos());  // Масштабируем координаты в 28 x 28 пикселей
      lastPoint = event->pos();
      update();  // Перерисовываем виджет
    }
  }

  void mouseReleaseEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton && drawing) {
      drawing = false;
    }
  }

  void paintEvent(QPaintEvent *event) override {
    if (event == nullptr) return;
    QPainter painter(this);

    // Масштабируем изображение до размеров виджета
    QImage scaledImage =
        image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(QPoint(0, 0), scaledImage);
  }

 private:
  QWidget *parent_;
  bool drawing;
  QPoint lastPoint;
  QImage image;
};

#endif  // DRAWINGWIDGET_H_
