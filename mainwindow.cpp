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

//vector<float> Rece_points;
//extern vector<vector<float>> AllPoint_vec;

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

    isSerialOpenFlag = false;
    setDia = new settingDialog(this);


    saveLocalDia = new saveLocalFile;
    saveThread = new QThread;
    saveLocalDia->moveToThread(saveThread);
    saveThread->start();


    receSerial_obj = new receSerial_msg;
    receSeri_thread = new QThread;
    receSerial_obj->moveToThread(receSeri_thread);
    receSeri_thread->start();


    int wid  = ui->widget->width();
    int height = ui->widget->height();

    ui->widget->helper.Window_wid = wid;
    ui->widget->helper.Window_height = height;




    //打开串口
    connect(setDia,SIGNAL(seriOpen_signal(bool)),receSerial_obj,SLOT(openOrCloseSerial_slot(bool)));  //配置窗口
    connect(setDia,SIGNAL(seriOpen_signal(bool)),this,SLOT(seriOpen_slot(bool)));  //配置窗口
    connect(this,SIGNAL(sendSerialSignal(QByteArray)),receSerial_obj,SLOT(sendSerialSlot(QByteArray)));

    //关闭串口
    connect(this,SIGNAL(seriOpen_signal(bool)),receSerial_obj,SLOT(openOrCloseSerial_slot(bool)));
    connect(receSerial_obj,SIGNAL(returnLinkInfo_signal(QString,bool)),this,SLOT(returnLinkInfo_slot(QString,bool)));



//    文件保存
    connect(receSerial_obj,SIGNAL(writeLogSignal(QString,int)),saveLocalDia,SLOT(writeLog(QString,int)));
    connect(this,SIGNAL(createDirSignal(QString)),saveLocalDia,SLOT(isDirExist(QString)));
    connect(this,SIGNAL(writeLogSignal(QString,int)),saveLocalDia,SLOT(writeLog(QString,int)));


//    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);  //串口读数据
    connect(ui->action,SIGNAL(triggered()),this,SLOT(showSettingDialog())); //菜单
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(closeConnect()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(showSaveFileDialog()));

    connect(&transTimer,SIGNAL(timeout()),this,SLOT(transCheckSlot()));
    connect(&saveDia,SIGNAL(saveSubmitSignal(bool,int,int)),this,SLOT(saveSubmitSlot(bool,int,int)));
    connect(setDia,SIGNAL(saveSubmitSignal(bool,int,int)),this,SLOT(saveSubmitSlot(bool,int,int)));



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
void MainWindow::seriOpen_slot(bool flag)
{
    ui->widget->isBeginWheel = true;

    ui->widget->timer.start(5);
    transTimer.start(1000);
    ui->showlabel_2->setText("  0 R/s");

    setDia->hide();


}

//@brief::关闭串口
void MainWindow::closeConnect()
{
    bool  flag = false;
    emit seriOpen_signal(flag);

    ui->widget->isBeginWheel = false;
    ui->widget->timer.stop();
    transTimer.stop();

    ui->showlabel_2->setText("0 R/s");
//    AllPoint_vec.clear();

    saveCircleNum = 0;  //保存标识清零

}

//!
//! \brief MainWindow::returnLinkInfo_slot
//!串口连接的返回信息
void MainWindow::returnLinkInfo_slot(QString str ,bool flag)
{
    if(false == flag)
    {
        if("open" == str)
        {
            QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("打开串口失败!"));
        }else if("close" == str)
        {
            QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("关闭串口失败!"));
        }
    }else
    {
        if("open" == str)
        {
            isSerialOpenFlag = true;
        }else if("close" == str)
        {
            isSerialOpenFlag = false;
        }
    }
}


void MainWindow::sendRotateSpeed_slot(float any,float speed)
{
    numOfCircle++;
    receRotation = speed;

}


//@brief:获取传输速率
void MainWindow::transCheckSlot()
{
    QString str = QString::number(numOfCircle)+"R/s";
    ui->showlabel_2->setText(str);
    numOfCircle = 0;

    QString str_2 = QString::number(receRotation)+"R/min";
    ui->Rotation_label->setText(str_2);


//    qDebug()<<"showCircleNum = "<<showCircleNum;
}

//接收是否保存文件命令，
void MainWindow::saveSubmitSlot(bool isSave,int circleNum, int radiusMeter)
{
    ui->widget->helper.radiusMeter = radiusMeter ;

    showCircleNum = circleNum + 1;

    receSerial_obj->showCircleNum = showCircleNum;

    receSerial_obj->saveFileIndex = 0;

    saveFileIndex = 0 ;  //文件保存 文件名序号设置为 0  ，初始为0

    cout<<"文件保存已经接收到了命令"<< " showCircleNum = "<<showCircleNum<<endl;

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currenttime = currentDateTime.toString("yyyy-MM-dd_hhmmss");

    if(true == isSave && isSaveFlag == false)  //之前没有设置保存
    {
        QString dirPath = saveDia.file_path + "/" + currenttime;

        if(dirPath.isEmpty())
        {
            QMessageBox::information(NULL,"warn","the Dir is empty,please check!");
        }else
        {
            emit createDirSignal(dirPath);
        }

        receSerial_obj->isSaveFlag = true;
        isSaveFlag = true;
    }

    isSaveFlag = isSave;

}



//!
//! \brief MainWindow::on_startRotate_pushButton_clicked
//!开始旋转的槽函数
void MainWindow::on_startRotate_pushButton_clicked()
{
    if(!isSerialOpenFlag)
    {
        QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("请先打开串口！"));
        return;
    }


    if(QStringLiteral("开始旋转") == ui->startRotate_pushButton->text())
    {
        QByteArray sendArray = "startlds$";
        emit sendSerialSignal(sendArray);


        ui->startRotate_pushButton->setText(QStringLiteral("停止旋转"));
    }else
    {
        QByteArray sendArray = "endlds$";
        emit sendSerialSignal(sendArray);
        ui->startRotate_pushButton->setText(QStringLiteral("开始旋转"));
    }

}
