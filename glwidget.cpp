#include "glwidget.h"
#include<QDebug>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

    elapsed = 0;
//    setFixedSize(200, 200);
    setAutoFillBackground(false);
    connect(&timer,SIGNAL(timeout()),this,SLOT(animate()));
//    timer.start(5);

    isBeginWheel =false;

}


void GLWidget::animate()
{
//    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    helper.Window_height = this->height();
    helper.Window_wid = this->width();
    x_radius = this->width()/2.0;
    y_radius = this->height()/2.0;

    painter.setRenderHint(QPainter::Antialiasing);
    helper.paint(&painter, event, elapsed);
    painter.end();
}


void GLWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {

        int x = e->x();
        int y = e->y();
        int clickangle;

        //如果在第一象限  0-89
        if(x>x_radius && (y<y_radius))
        {
            float xOffset = x-x_radius;
            float yOffset = y_radius-y;
            float res = xOffset/yOffset;
            float ang = atanf(res);
            clickangle = ang*180.0/3.1415926;

            qDebug()<<"x="<<x<<"  y="<<y<<"  xOffset="<<xOffset<<" yOffset="<<yOffset<<"  ang="<<ang;
        }

        //如果在第二象限   270 -359
        else if((x<x_radius) && (y<y_radius))
        {
            float xOffset = x_radius-x;
            float yOffset = y_radius-y;
            float res = xOffset/yOffset;
            float ang = atanf(res);
            clickangle = 360 - ang*180/3.1415926;
        }

        //如果在第三象限    180-269
        else if((x<x_radius) && (y>y_radius))
        {
            float xOffset = x_radius-x;
            float yOffset = y - y_radius;
            float res = xOffset/yOffset;
            float ang = atanf(res);
            clickangle = 180+ ang*180/3.1415926;
        }

        //如果在第四想想  90-179
        else if((x>x_radius) && (y>y_radius))
        {
            float xOffset = x - x_radius;
            float yOffset = y - y_radius;
            float res = xOffset/yOffset;
            float ang = atanf(res);
            clickangle = 180 - ang*180/3.1415926;
        }

        QString str ="angle="+QString::number(clickangle) + ",Dis="+QString::number(e->y());

        qDebug()<<str;
//        QToolTip::showText(QCursor::pos(),str);

        helper.clickAngle = clickangle;
    }
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(!isBeginWheel)
        return;

    if(event->delta() > 0) //当滚轮向上滑，远离使用者
    {
        helper.rotate += 0.006;

    }
    else //当滚轮向下滑，靠近使用者
    {
        helper.rotate -= 0.006;
        if(helper.rotate < 0)
            helper.rotate = 0.001;
    }
}
