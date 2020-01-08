#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<vector>
#include<iostream>
#include "QMenu"
#include "QMenuBar"
#include "QAction"
#include "QMessageBox"
#include "QFileDialog"
#include<QDateTime>
#include<QDate>
#include<time.h>
using namespace std;

vector<float> Rece_points;
extern vector<vector<float>> AllPoint_vec;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaveFlag = false;
    saveCircleNum = 0;
    showCircleNum = 2;
    numOfCircle = 0;
    receRotation = 0;

    saveFileIndex = 0;
    setDia = new settingDialog(this);
    serial = new QSerialPort(this);

    saveLocalDia = new saveLocalFile;
    saveThread = new QThread;
    saveLocalDia->moveToThread(saveThread);
    saveThread->start();


    int wid  = ui->widget->width();
    int height = ui->widget->height();

    ui->widget->helper.Window_wid = wid;
    ui->widget->helper.Window_height = height;


//    float ang = 0;
//    for(int i=0; i<360*4; i++)
//    {
//        Rece_points.push_back(ang);
//        Rece_points.push_back(1000);
//        ang += 0.5;

//    }
//     AllPoint_vec.push_back(Rece_points);




    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);  //串口读数据
    connect(ui->action,SIGNAL(triggered()),this,SLOT(showSettingDialog())); //菜单
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(closeConnect()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(showSaveFileDialog()));
    connect(setDia,SIGNAL(seriOpen_signal()),this,SLOT(seriOpen_slot()));  //配置窗口
    connect(&transTimer,SIGNAL(timeout()),this,SLOT(transCheckSlot()));
    connect(&saveDia,SIGNAL(saveSubmitSignal(bool,int,int)),this,SLOT(saveSubmitSlot(bool,int,int)));
    connect(setDia,SIGNAL(saveSubmitSignal(bool,int,int)),this,SLOT(saveSubmitSlot(bool,int,int)));

    //write log
    connect(this,SIGNAL(createDirSignal(QString)),saveLocalDia,SLOT(isDirExist(QString)));
    connect(this,SIGNAL(writeLogSignal(QString,int)),saveLocalDia,SLOT(writeLog(QString,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//@brief:打开串口设置界面
void MainWindow::showSettingDialog()
{
    setDia->show();
}

//@brief:打开文件保存界面
void MainWindow::showSaveFileDialog()
{
    saveDia.show();

}


//@brief:打开串口
void MainWindow::seriOpen_slot()
{
    ui->widget->isBeginWheel = true;


//    //如果保存接收文件，则先创建文件夹
//    if(true == isSaveFlag)
//    {
//        if(fullDirPath.isEmpty())
//        {
//            QDateTime dt;
//            QTime time;
//            QDate date;
//            dt.setDate(date.currentDate());
//            QString currenttime = dt.toString("yyyy-MM-dd");
//            fullDirPath = saveDia.file_path + "/" + currenttime;
//        }
//        qDebug()<<"open seri ,fullDirPath ="<< fullDirPath<<endl;
//        emit createDirSignal(fullDirPath);
//    }


    qDebug()<<"seriOpen_slot() has coming"<<endl;

    serial->setPortName(setDia->currentSettings.name);
    serial->setBaudRate(setDia->currentSettings.baudRate);
    serial->setDataBits(setDia->currentSettings.dataBits);
    serial->setParity(setDia->currentSettings.parity);
    serial->setStopBits(setDia->currentSettings.stopBits);
    serial->setFlowControl(setDia->currentSettings.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
    }


    ui->widget->timer.start(1);
    transTimer.start(1000);
//     qDebug()<<"name="<<currentSettings.name<<" baudRate ="<<currentSettings.baudRate<<" dataBits="<<currentSettings.dataBits<<" parity="<<currentSettings.parity<<" stopBits="<<currentSettings.stopBits<<" flowCon"<<currentSettings.flowControl;

//     ui->labIsOpen->setText("串口状态：打开");
//     ui->label_show_2->setText("5 ms ");
//     ui->btnOpen->setText("关闭串口");
    ui->showlabel_2->setText("  0 R/s");

    setDia->hide();


}

//@brief::关闭串口
void MainWindow::closeConnect()
{
    ui->widget->isBeginWheel = false;
    serial->close();
    ui->widget->timer.stop();
    transTimer.stop();

    ui->showlabel_2->setText("0 R/s");
//    AllPoint_vec.clear();

    saveCircleNum = 0;  //保存标识清零

}


//读取端口的数据
// FA A0 SS SS DD DD DD DD .....  XX
//!
//! \brief MainWindow::readData
//!整个协议62个字节 数据区32个字节
void MainWindow::readData()
{
    QByteArray temp = serial->readAll();
    QString strHex;//16进制数据

    int singleLen = 62*2;

    if (!temp.isEmpty())
    {
        QDataStream out(&temp,QIODevice::ReadWrite);
        while (!out.atEnd())
        {
            qint8 outChar=0;
            out>>outChar;
            QString str=QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0'));

            if (str.length()>1)
            {
                strHex+=str;
            }
            else
            {
                strHex+="0"+str;
            }
        }
        strHex = strHex.toUpper();
//        qDebug()<<strHex;
//        return;

        m_buffer.append(strHex);

        int totallen = m_buffer.size();
        while(totallen)
        {
            if(totallen <singleLen)    //一个报文至少要有66个字节
                return;

           int indexOf5A = m_buffer.indexOf("FA",0);
           if(indexOf5A < 0)  //没有找到5A
           {
               qDebug()<<QString::fromUtf8("msg maybe error,can't find FA")<<"index ="<<indexOf5A<<"buffer"<<m_buffer<<endl;
               return;
           }else if(indexOf5A>0)  //第一次的时候前面会有冗余数据，删掉
           {
               m_buffer = m_buffer.right(totallen-indexOf5A);
               totallen = m_buffer.size();
               qDebug()<<"the first msg ,has some Redundant data,  indexOf5A="<<indexOf5A<<"  the left msg = "<<m_buffer<<endl;
               if(totallen <singleLen)
                   return;
           }

           //以下数据为FA打头数据
           //进行校验的操作
           QString single_Data = m_buffer.left(singleLen);     //一帧数据
//           qDebug()<<"singleData = "<<single_Data;

           if(!msgCheck(single_Data))
           {
               qDebug()<<"msgCheck error!  single_Data ="<< single_Data <<endl;
               m_buffer = m_buffer.right(totallen - 2);
               totallen = m_buffer.size();
               return;
           }

           //报文顺序标识 0xA0-0xF9:  0xA0: 0,1,2,3
           int index = single_Data.mid(2,2).toInt(NULL,16);
           if(index<160 || index>249)
           {
               qDebug()<<"index beyond the tolence,the dataAnalye mayebe error ,index = "<< index<<"  single_Data"<<  single_Data <<endl;
               m_buffer = m_buffer.right(totallen - 2);
               totallen = m_buffer.size();
               return;
           }
           firstAngle = (index-160)*4;        //每一组的第一个点对应的角度  1度的分辨率

           //转速：2bytes 04 00
           QString RotationSpeed_str = single_Data.mid(6,2) + single_Data.mid(4,2);
           float tmpRotation_ = RotationSpeed_str.toInt(NULL,16);
           receRotation = tmpRotation_ / 100.0;         //实际值扩大100倍

           //一个包存储了16个点的数据
           QString distanceStr;
           int distanceInt;
           float angleTmp = firstAngle;
           distanceStr = single_Data.mid(8+2,2) + single_Data.mid(8,2);
           int distanceInt_1 =  distanceStr.toInt(NULL,16);
           for(int i=0; i<64; i+=4)
           {
               distanceStr = single_Data.mid(8+i+2,2) + single_Data.mid(8+i,2);
               distanceInt = distanceStr.toInt(NULL,16);
               Rece_points.push_back(angleTmp);
               Rece_points.push_back(distanceInt);
               angleTmp += 0.25;       //每个点相邻0.25度
           }

//            qDebug()<<" singleData = "<<single_Data<<"firstAngle = "<<firstAngle<<"  distanceInt_1="<<distanceInt_1<<endl;
            QString saveData = single_Data+"  "+ QString::number(firstAngle) +"  " + QString::number(distanceInt_1)  ;

//            qDebug()<<"saveData = "<<saveData;

            //生成数据文件
            if(true == isSaveFlag  && saveCircleNum >= 3)
            {
               saveFileIndex++;
               saveCircleNum = 5;  //设置为一个大于3的数字即可
               emit writeLogSignal(saveData,saveFileIndex);
            }

           if(356 == firstAngle && (!Rece_points.empty()) )  //360度已经接收完毕
           {
               saveCircleNum++;
               numOfCircle++;

               AllPoint_vec.push_back(Rece_points);
               Rece_points.clear();

               if(AllPoint_vec.size() == showCircleNum)  //循环清理第一个元素
               {
                   AllPoint_vec.erase(AllPoint_vec.begin(),AllPoint_vec.begin()+1);

               }
               if(AllPoint_vec.size() > showCircleNum)
               {
                   AllPoint_vec.clear();
               }
           }

           m_buffer = m_buffer.right(totallen - singleLen);
           totallen = m_buffer.size();
//         qDebug()<<"total ="<<totallen<<endl;

        }
    }
}

//和校验   前58个字节求和  和校验字节 对比看是否相等
bool MainWindow:: msgCheck(QString msg)
{
    QString strCmd = msg;
    strCmd = strCmd.replace(" ","");
    int len = strCmd.length();

    int sunNum = 0;
    int i=0;
    for(i=0; i<len-4; i+=2)
    {
        sunNum += strCmd.mid(i,2).toInt(NULL,16);
    }

    QString checkStr = strCmd.mid(i+2,2) + strCmd.mid(i,2);
    int checkNum = checkStr.toInt(NULL,16);

    if(sunNum == checkNum)
    {
        return true;
    }else
    {
        return false;
    }
}

int MainWindow::findComplement(int num)
{
    int sum = 0;
    int i = 0;
    while(sum<num){
      sum += pow(2,i);//2的i次方
      i++;
  }
  return sum-num;
}

//@brief:获取传输速率
void MainWindow::transCheckSlot()
{
    QString str = QString::number(numOfCircle)+"R/s";
    ui->showlabel_2->setText(str);
    numOfCircle = 0;

    QString str_2 = QString::number(receRotation)+"R/min";
    ui->Rotation_label->setText(str_2);


    qDebug()<<"showCircleNum = "<<showCircleNum;
}

//接收是否保存文件命令，
void MainWindow::saveSubmitSlot(bool isSave,int circleNum, int radiusMeter)
{
    ui->widget->helper.radiusMeter = radiusMeter ;

    showCircleNum = circleNum + 1;

    saveFileIndex = 0 ;  //文件保存 文件名序号设置为 0  ，初始为0

    cout<<"文件保存已经接收到了命令"<< " showCircleNum = "<<showCircleNum<<endl;

    QDateTime dt;
    QTime time;
    QDate date;
    dt.setDate(date.currentDate());
    QString currenttime = dt.toString("yyyy-MM-dd");

    if(true == isSave && isSaveFlag == false)  //之前没有设置保存
    {
        QString dirPath = saveDia.file_path + "/" + currenttime;
        if(serial->isOpen())    //如果端口打开则创建，否则不创建
        {
            if(dirPath.isEmpty())
            {
                QMessageBox::information(NULL,"warn","the Dir is empty,please check!");
            }else
            {

                emit createDirSignal(dirPath);
            }

        }
//        fullDirPath = dirPath;
        isSaveFlag = true;
    }

    isSaveFlag = isSave;

}



//!
//! \brief MainWindow::on_startRotate_pushButton_clicked
//!开始旋转的槽函数
void MainWindow::on_startRotate_pushButton_clicked()
{
    if(!serial->isOpen())
    {
        QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("请先开启串口！"));
        return;
    }
    if(QStringLiteral("开始旋转") == ui->startRotate_pushButton->text())
    {
        if(serial->isWritable())
        {
            QByteArray sendArray = "startlds$";
            serial->write(sendArray);
            serial->flush();
        }

        ui->startRotate_pushButton->setText(QStringLiteral("停止旋转"));
    }else
    {
        if(serial->isWritable())
        {
            QByteArray sendArray = "endlds$";
            serial->write(sendArray);
            serial->flush();
        }
        ui->startRotate_pushButton->setText(QStringLiteral("开始旋转"));
    }

}
