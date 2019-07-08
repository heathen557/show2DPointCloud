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

 vector<int> Rece_points;
extern vector<vector<int>> AllPoint_vec;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSaveFlag = false;
    saveCircleNum = 0;
    showCircleNum = 2;
    setDia = new settingDialog(this);
    serial = new QSerialPort(this);

    int wid  = ui->widget->width();
    int height = ui->widget->height();

    ui->widget->helper.Window_wid = wid;
    ui->widget->helper.Window_height = height;

    qDebug()<<"wid="<<wid<<"  height="<<height<<endl;


    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);  //串口读数据
    connect(ui->action,SIGNAL(triggered()),this,SLOT(showSettingDialog())); //菜单
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(closeConnect()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(showSaveFileDialog()));
    connect(setDia,SIGNAL(seriOpen_signal()),this,SLOT(seriOpen_slot()));  //配置窗口
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
    qDebug()<<"has coming"<<endl;
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
    //如果保存接收文件，则先创建文件夹
    if(true == isSaveFlag)
    {
        isDirExist(fullDirPath);
    }


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
    ui->showlabel_1->setText("200 f/s");
    ui->showlabel_2->setText("  0 R/s");

    setDia->hide();


}

//@brief::关闭串口
void MainWindow::closeConnect()
{
    serial->close();
    ui->widget->timer.stop();
    transTimer.stop();

    ui->showlabel_1->setText("0 f/s");
    ui->showlabel_2->setText("0 R/s");
    AllPoint_vec.clear();

    saveCircleNum = 0;  //保存标识清零
}


//读取端口的数据
void MainWindow::readData()
{
    QByteArray temp = serial->readAll();
    QString strHex;//16进制数据

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
                strHex+=str+" ";
            }
            else
            {
                strHex+="0"+str+" ";
            }
        }
        strHex = strHex.toUpper();
        m_buffer.append(strHex);

        int totallen = m_buffer.size();
        while(totallen)
        {
            if(totallen <27)
                return;

           int indexOf5A = m_buffer.indexOf("5A 03 04 ",0);
           if(indexOf5A < 0)  //没有找到5A
           {
               qDebug()<<QString::fromUtf8("接收数据有误，不存在5A")<<"index ="<<indexOf5A<<"buffer"<<m_buffer<<endl;
               return;
           }else if(indexOf5A>0)  //第一次的时候前面会有冗余数据，删掉
           {
               m_buffer = m_buffer.right(totallen-indexOf5A);
               totallen = m_buffer.size();
               if(totallen <27)
                   return;
           }

           //以下数据为5A打头数据

           //进行和校验
           QString single_Data = m_buffer.left(27);
           if(!msgCheck(single_Data))
                return;


           //获取角度信息
           QString angle_str_ = single_Data.mid(12,5);
           angle_str_ = angle_str_.replace(" ", "");
           QString s1=angle_str_[0];
           QString s2=angle_str_[1];
           QString s3=angle_str_[2];
           QString s4=angle_str_[3];
           QString angle_str = s3+s4+s1+s2;
           int angleInt = angle_str.toInt(NULL,16);
//           qDebug()<<"角度"<<QString::number(angleInt);

           //获取距离信息(mm)
           QString distance_str_ = single_Data.mid(18,5);
           distance_str_ = distance_str_.replace(" ", "");
           s1=distance_str_[0];
           s2=distance_str_[1];
           s3=distance_str_[2];
           s4=distance_str_[3];
           QString distance_str = s3+s4+s1+s2;
           int distanceInt = distance_str.toInt(NULL,16);
//           qDebug()<<"距离"<<QString::number(distanceInt);

//            qDebug()<<" singleData = "<<single_Data<<"angle = "<<angleInt<<"  distance="<<distanceInt<<" x="<<x <<" y="<<y<<endl;
            QString saveData = single_Data+"  "+ QString::number(angleInt) +"  " + QString::number(distanceInt)  ;

            //生成数据文件
            if(true == isSaveFlag  && saveCircleNum >= 3)
            {
                writeLog(saveData,saveCircleNum-3);
            }

           if(angleInt<lastAngleInt && (!Rece_points.empty()) )  //360度已经接收完毕 且只存储6个
           {
               saveCircleNum++;
               numOfCircle++;

               AllPoint_vec.push_back(Rece_points);
               Rece_points.clear();
//               qDebug()<<"已经接收了***************"<<AllPoint_vec.size()<<endl;

               if(AllPoint_vec.size() >= showCircleNum)  //循环清理第一个元素
               {
                   AllPoint_vec.erase(AllPoint_vec.begin(),AllPoint_vec.begin()+1);
               }


           }
           lastAngleInt = angleInt;


           Rece_points.push_back(angleInt);
           Rece_points.push_back(distanceInt);
//           qDebug()<<"vector's len = "<<Rece_points.size();


           m_buffer = m_buffer.right(totallen - 27);
           totallen = m_buffer.size();
//         qDebug()<<"total ="<<totallen<<endl;



        }
    }
}

//和校验
bool MainWindow:: msgCheck(QString msg)
{
    QString str1 = msg.mid(3,2);
    QString str2 = msg.mid(6,2);
    QString str3 = msg.mid(9,2);
    QString str4 = msg.mid(12,2);
    QString str5 = msg.mid(15,2);
    QString str6 = msg.mid(18,2);
    QString str7 = msg.mid(21,2);
    QString str8 = msg.mid(24,2);

    int num = str1.toInt(NULL,16)+str2.toInt(NULL,16)+str3.toInt(NULL,16)+str4.toInt(NULL,16)+str5.toInt(NULL,16)+str6.toInt(NULL,16)+str7.toInt(NULL,16);
//    qDebug()<<num<<"    "<<findComplement(num);

    if(findComplement(num) == str8.toInt(NULL,16))
    {
        return true;
    }else
    {
        false;
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
}

//接收是否保存文件命令，
void MainWindow::saveSubmitSlot(bool isSave,int circleNum, int radiusMeter)
{
    ui->widget->helper.radiusMeter = radiusMeter ;


    cout<<"文件保存已经接收到了命令"<<endl;
    showCircleNum = circleNum + 1;

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
            isDirExist(dirPath);
        }
//        fullDirPath = dirPath;
        isSaveFlag = true;
    }

}


//@brief:判断文件夹是否存在,不存在则创建
bool MainWindow::isDirExist(QString fullPath)
{
    qDebug()<<"即将要进行判断的目录为:"<<fullPath<<endl;
    QDir dir(fullPath);
    if(dir.exists())
    {
      qDebug()<<fullPath<<"已经存在"<<endl;
      dirCurIndex++;
      fullDirPath = fullPath + "_1";
      isDirExist(fullDirPath);
      return true;
    }
    else
    {
       qDebug()<<"fullDirPath = "<<fullPath<<endl;
       fullDirPath = fullPath;
       dirCurIndex = 0;
       bool ok = dir.mkdir(fullDirPath);//只创建一级子目录，即必须保证上级目录存在
       return ok;
    }
}


//按照标识写文件
// input:text:写入文本的内容
// numOfFile：第几个文件
void MainWindow::writeLog(QString text,int numOfFile)
{

//    qDebug()<<"初始化时 槽函数已经进来 "<<endl;
//    ui->widget->helper.radiusMeter = radiusMeter ;   //显示半径到底要多少米

    QString sFilePath=fullDirPath + "/"+QString::number(numOfFile)+".txt";
    QFile file(sFilePath);
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);

    QTextStream out(&file);
    out<<text.toLocal8Bit()<<endl;
    file.close();


}
