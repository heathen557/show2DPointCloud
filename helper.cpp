/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include<QDebug>


QMutex m_mutex;
vector<vector<float>> AllPoint_vec;

#define pi 3.14159

//! [0]
Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(0, 0, 0));
    circleBrush = QBrush(gradient);
//    circlePen = QPen(Qt::black);
    circlePen = QPen(Qt::white);

    axiPen = QPen(Qt::gray);
    axiPen.setMiterLimit(0.2);

    circlePen.setWidthF(1);
    textPen = QPen(Qt::green);
    textFont.setPixelSize(50);



    rotate = 0.01;


   clickAngle = 0;
   ang = 0;
   distance = 0;
   show_x = 0;
   show_y = 0;
   showDistance = 0;



}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{

    m_mutex.lock();
    AllPoint_vec_ = AllPoint_vec;
    m_mutex.unlock();

//    qDebug()<<"paint";

//    qDebug()<<" wid is  ==== "<<Window_wid<<endl;
//    qDebug()<<" height is  ==== "<<Window_height<<endl;
//    qDebug()<<"half wid is  ==== "<<Window_wid/2<<endl;
//    qDebug()<<"half height is  ==== "<<Window_height/2<<endl;
//    qDebug()<<"the show  AllPoint_vec's len = "<<AllPoint_vec.size()<<endl;



    painter->fillRect(event->rect(), background);

//    qDebug()<<"event->rect = "<<event->rect().width()<<"   "<<event->rect().height();

    painter->save();

    painter->setPen(axiPen);




    //************************************

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawLine(QPoint(0,Window_height/2),QPoint(Window_wid,Window_height/2));
    painter->drawLine(QPoint(Window_wid/2,0),QPoint(Window_wid/2,Window_height));

    painter->setPen(circlePen);
    QPointF pointf[10000];
    int allLen = AllPoint_vec_.size();

//    qDebug()<<"allLen = "<<allLen;

    for(int m=0; m<allLen; m++)
    {
        int len =AllPoint_vec_[m].size();
        int pointNum = 0;
        for(int n=0; n<len-1; n+=2)
        {
            pointf[pointNum].setX(0);
            pointf[pointNum].setY(0);

            ang = AllPoint_vec_[m][n];
            distance = AllPoint_vec_[m][n+1];




            //半径的像素个数为300，显示30米时,distance = 30000 ; 缩放系数为：30000/300 = 100
            //显示15米时, 缩放系数为：15000/300 = 50
            //显示x米时， 缩放系数为：1000x/300 =10/3*x
            //当distance > 1000x时， distance = 1000x;
            /*
             *        半径像素     显示像素距离
             *     ---------- = -------------
             *     设置的最大距离    当前的距离
             * */

            //  distance的单位是毫米 记得显示的最大值为10米
//            if(radiusMeter < 1)
//            {
//                radiusMeter = 10 ;  //缺省为10米
//             }

            if(distance > 1000*10)     //超过10m统一设置为10M
            {
                distance = 1000.0 * 10 ;
            }

            double x = distance * sin(ang/180.0*pi) * rotate;
            double y = -1 * distance * cos(ang/180.0*pi) * rotate;

//            qDebug()<<"ang="<<ang<<"  x="<<x<<"  y="<<y;

            if(ang == clickAngle)
            {
                show_x = x;
                show_y = y;
                showDistance = distance;

//                qDebug()<<"clickAngle="<<clickAngle<<"   show_x="<<show_x<<"   show_y="<<show_y;
            }

            pointf[pointNum].setX(x + Window_wid/2.0);
            pointf[pointNum].setY(y + Window_height/2.0);

            pointNum++;
            painter->drawPoints(pointf,pointNum);

        }
    }

//    AllPoint_vec.clear();



    //************************************

    painter->restore();

//! [3]
    painter->setPen(textPen);
//    painter->setFont(textFont);
    painter->drawText(QRect(Window_wid-30, Window_height/2, 30, 20), Qt::AlignCenter, QStringLiteral("90°"));
    painter->drawText(QRect(Window_wid/2, 0, 30, 20), Qt::AlignCenter, QStringLiteral("0°"));
    painter->drawText(QRect(Window_wid/2, Window_height-20, 30, 20), Qt::AlignCenter, QStringLiteral("180°"));
    painter->drawText(QRect(0, Window_height/2, 30, 20), Qt::AlignCenter, QStringLiteral("270°"));


    QString strShow = QString::number(clickAngle)+QStringLiteral("°; ") +QString::number(showDistance) + "mm";
    painter->drawText(QRect(Window_wid/2.0+show_x, Window_height/2.0+show_y-15, 100, 30), Qt::AlignCenter, strShow);
}
//! [3]
