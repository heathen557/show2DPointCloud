#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include<helper.h>
#include <QPainter>
#include <QTimer>
#include<QMouseEvent>
#include<QToolTip>
#include<math.h>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    Helper helper;
    QTimer timer;

    void mousePressEvent(QMouseEvent *e);

    void wheelEvent(QWheelEvent *event);

    bool isBeginWheel;

    float x_radius;
    float y_radius;

signals:

public slots:
    void animate();
    void paintEvent(QPaintEvent *event) override;


private:

    int elapsed;

};

#endif // GLWIDGET_H
