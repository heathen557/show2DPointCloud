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
#include<vector>
#include<iostream>
#include<math.h>
using namespace std;

vector<vector<int>> AllPoint_vec;

//! [0]
Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 64, 64));
    circleBrush = QBrush(gradient);
//    circlePen = QPen(Qt::black);
    circlePen = QPen(Qt::white);

    axiPen = QPen(Qt::white);
    axiPen.setMiterLimit(0.2);


    QVector<qreal> dashes;
    qreal space = 5;
    dashes << 1<< space << 1 <<space;
    axiPen.setDashPattern(dashes);

    circlePen.setWidthF(1);
    textPen = QPen(Qt::green);
    textFont.setPixelSize(50);


}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
//    qDebug()<<" wid is  ==== "<<Window_wid<<endl;
//    qDebug()<<" height is  ==== "<<Window_height<<endl;
    qDebug()<<"half wid is  ==== "<<Window_wid/2<<endl;
    qDebug()<<"half height is  ==== "<<Window_height/2<<endl;
//    qDebug()<<"the show  AllPoint_vec's len = "<<AllPoint_vec.size()<<endl;

    painter->fillRect(event->rect(), background);
//    painter->translate(100, 100);
//! [1]

//! [2]
    painter->save();
//    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
//    painter->rotate(elapsed * 0.030);

    //************************************


    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawLine(QPoint(0,Window_height/2),QPoint(Window_wid,Window_height/2));
    painter->drawLine(QPoint(Window_wid/2,0),QPoint(Window_wid/2,Window_height));

    QPointF pointf[10000];
    int allLen = AllPoint_vec.size();
    for(int m=0; m<allLen; m++)
    {
        int len =AllPoint_vec[m].size();
        int pointNum = 0;
        for(int n=0; n<len-1; n+=2)
        {
            pointf[pointNum].setX(0);
            pointf[pointNum].setY(0);

            int ang = AllPoint_vec[m][n];
            int distance = AllPoint_vec[m][n+1];
//            qDebug()<<"ang="<<ang/10.0<<"  distance="<<distance<<endl;

            //半径的像素个数为300，显示30米时,distance = 30000 ; 缩放系数为：30000/300 = 100
            //显示15米时, 缩放系数为：15000/300 = 50
            //显示x米时， 缩放系数为：1000x/300 =10/3*x
            //当distance > 1000x时， distance = 1000x;

            if(distance > 1000*radiusMeter)
            {
                distance = 1000.0 * radiusMeter ;
            }
            float coefficient = 1000.0 * radiusMeter/300.0;



            double x = distance * sin(ang/10.0/180.0*3.14)/coefficient;
            double y = -1 * distance * cos(ang/10.0/180.0*3.14)/coefficient;

            pointf[pointNum].setX(x + Window_wid/2.0);
            pointf[pointNum].setY(y + Window_height/2.0);

            pointNum++;
            painter->drawPoints(pointf,pointNum);

        }
    }

//    AllPoint_vec.clear();



    //************************************

    painter->setPen(circlePen);
    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
//        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
//        painter->drawEllipse(QRectF(-10+Window_wid/2, -10+Window_height/2,
//                                    20, 20));
//        painter->drawEllipse(QRectF(-20+Window_wid/2, -20+Window_height/2,
//                                    40, 40));
//        painter->drawEllipse(QRectF(-30+Window_wid/2, -30+Window_height/2,
//                                    60, 60));
//        painter->drawEllipse(QRectF(-40+Window_wid/2, -40+Window_height/2,
//                                    80, 80));
//        painter->drawEllipse(QRectF(-50+Window_wid/2, -50+Window_height/2,
//                                    100, 100));
//        painter->drawEllipse(QRectF(-60+Window_wid/2, -60+Window_height/2,
//                                    120, 120));
//        painter->drawEllipse(QRectF(-70+Window_wid/2, -70+Window_height/2,
//                                    140, 140));
//        painter->drawEllipse(QRectF(-80+Window_wid/2, -80+Window_height/2,
//                                    160, 160));
//        painter->drawEllipse(QRectF(-90+Window_wid/2, -90+Window_height/2,
//                                    180, 180));
//        painter->drawEllipse(QRectF(-100+Window_wid/2, -100+Window_height/2,
//                                    200, 200));


//        painter->drawEllipse(QRectF(-50+Window_wid/2, -50+Window_height/2,
//                                    100, 100));
//        painter->drawLine(QRectF(0, 25,
//                                 20, 20));

        //坐标轴画线
//        painter->drawLine(QPoint(0,Window_height/2),QPoint(Window_wid,Window_height/2));
//        painter->drawLine(QPoint(Window_wid/2,0),QPoint(Window_wid/2,Window_height));


        //30度
//        double x1 = Window_wid/2+Window_height/2*tan(60.0/180.0*3.1415925);
//        double x2 = Window_wid/2-Window_height/2*tan(60.0/180.0*3.1415925);
//        painter->drawLine(QPoint(x1,0),QPoint(x2,Window_height));

//        x1 = Window_wid/2+Window_height/2*tan(30.0/180.0*3.1415925);
//        x2 = Window_wid/2-Window_height/2*tan(30.0/180.0*3.1415925);
//        painter->drawLine(QPoint(x1,0),QPoint(x2,Window_height));

//        x1 = Window_wid/2-Window_height/2*tan(60.0/180.0*3.1415925);
//        x2 = Window_wid/2+Window_height/2*tan(60.0/180.0*3.1415925);
//        painter->drawLine(QPoint(x1,0),QPoint(x2,Window_height));

//        x1 = Window_wid/2-Window_height/2*tan(30.0/180.0*3.1415925);
//        x2 = Window_wid/2+Window_height/2*tan(30.0/180.0*3.1415925);
//        painter->drawLine(QPoint(x1,0),QPoint(x2,Window_height));



//        QPointF pointf[10000];
//        for(int j=0; j<100; j++)
//        {
//            pointf[j].setX(2.0+i*8);
//            pointf[j].setY(103+i);
//        }


//        painter->drawPoints(pointf,10000);
//        painter->drawPoint(700,520);



    }
    painter->restore();
//! [2]

//! [3]
    painter->setPen(textPen);
//    painter->setFont(textFont);
    painter->drawText(QRect(Window_wid-30, Window_height/2, 30, 20), Qt::AlignCenter, QStringLiteral("90"));
    painter->drawText(QRect(Window_wid/2, 0, 30, 20), Qt::AlignCenter, QStringLiteral("0"));
    painter->drawText(QRect(Window_wid/2, Window_height-20, 30, 20), Qt::AlignCenter, QStringLiteral("180"));
    painter->drawText(QRect(0, Window_height/2, 30, 20), Qt::AlignCenter, QStringLiteral("270"));
}
//! [3]
