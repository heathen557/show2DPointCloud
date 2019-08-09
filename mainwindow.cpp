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

    saveLocalDia = new saveLocalFile;
    saveThread = new QThread;
    saveLocalDia->moveToThread(saveThread);
    saveThread->start();


    int wid  = ui->widget->width();
    int height = ui->widget->height();

    ui->widget->helper.Window_wid = wid;
    ui->widget->helper.Window_height = height;



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
    //如果保存接收文件，则先创建文件夹
    if(true == isSaveFlag)
    {
        if(fullDirPath.isEmpty())
        {
            QDateTime dt;
            QTime time;
            QDate date;
            dt.setDate(date.currentDate());
            QString currenttime = dt.toString("yyyy-MM-dd");
             fullDirPath = saveDia.file_path + "/" + currenttime;
        }
        qDebug()<<"open seri ,fullDirPath ="<< fullDirPath<<endl;
        emit createDirSignal(fullDirPath);
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
            if(totallen <66)    //一个报文至少要有66个字节
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
               if(totallen <66)
                   return;
           }

           //以下数据为FA打头数据
           //进行校验的操作
           QString single_Data = m_buffer.left(66);     //一帧数据
           if(!msgCheck(single_Data))
           {
               qDebug()<<"msgCheck error!  single_Data ="<< single_Data <<endl;
               m_buffer = m_buffer.right(totallen - 3);
               totallen = m_buffer.size();
               return;
           }

           //报文顺序标识 0xA0-0xF9:  0xA0: 0,1,2,3
           int index = single_Data.mid(3,2).toInt(NULL,16);
           if(index<160 || index>249)
           {
               qDebug()<<"index beyond the tolence,the dataAnalye mayebe error ,index = "<< index<<"  single_Data"<<  single_Data <<endl;
               m_buffer = m_buffer.right(totallen - 3);
               totallen = m_buffer.size();
               return;
           }
           firstAngle = (index-160)*4;                //每一组的第一个点对应的角度

           //转速：2bytes 04 00
           QString RotationSpeed_str = single_Data.mid(6,5);

           //获取距离信息1      12 0C  PEAK: 88 13
           QString distance_str1_ = single_Data.mid(15,2) + single_Data.mid(12,2);
//           QString peak_str1 = single_Data.mid(21,2) + single_Data.mid(18,2);
           int distanceInt_1 = distance_str1_.toInt(NULL,16);
           Rece_points.push_back(firstAngle*10);
           Rece_points.push_back(distanceInt_1);


           //获取距离信息2      3F 5A  PEAK: 03 04
           QString distance_str2_ = single_Data.mid(27,2) + single_Data.mid(24,2);
//           QString peak_str2 = single_Data.mid(33,2) + single_Data.mid(30,2);
           int distanceInt_2 = distance_str2_.toInt(NULL,16);
           secondAngle = firstAngle + 1;
           Rece_points.push_back(secondAngle*10);
           Rece_points.push_back(distanceInt_2);

           //获取距离信息3      00 12  PEAK: 0C 88
           QString distance_str3_ = single_Data.mid(39,2) + single_Data.mid(36,2);
//           QString peak_str3 = single_Data.mid(45,2) + single_Data.mid(42,2);
           int distanceInt_3 = distance_str3_.toInt(NULL,16);
           thirdAngle = firstAngle + 2;
           Rece_points.push_back(thirdAngle*10);
           Rece_points.push_back(distanceInt_3);

           //获取距离信息4      13 3F  PEAK:3F 4F
           QString distance_str4_ = single_Data.mid(51,2) + single_Data.mid(48,2);
//           QString peak_str4 = single_Data.mid(57,2) + single_Data.mid(54,2);
           int distanceInt_4 = distance_str4_.toInt(NULL,16);
           fourAngle = firstAngle + 3;
           Rece_points.push_back(fourAngle*10);
           Rece_points.push_back(distanceInt_4);

            qDebug()<<" singleData = "<<single_Data<<"firstAngle = "<<firstAngle<<"  distanceInt_1="<<distanceInt_1<<endl;
            QString saveData = single_Data+"  "+ QString::number(firstAngle) +"  " + QString::number(distanceInt_1)  ;

            //生成数据文件
            if(true == isSaveFlag  && saveCircleNum >= 3)
            {
//             writeLog(saveData,saveCircleNum-3);
               emit writeLogSignal(saveData,saveCircleNum-3);
            }

           if(359 == fourAngle && (!Rece_points.empty()) )  //360度已经接收完毕
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

           m_buffer = m_buffer.right(totallen - 66);
           totallen = m_buffer.size();
//         qDebug()<<"total ="<<totallen<<endl;

        }
    }
}

//和校验
bool MainWindow:: msgCheck(QString msg)
{

    QString str1 = msg.mid(3,2)+ msg.mid(0,2);
    QString str2 = msg.mid(9,2)+ msg.mid(6,2);
    QString str3 = msg.mid(15,2)+ msg.mid(12,2);
    QString str4 = msg.mid(21,2)+ msg.mid(18,2);
    QString str5 = msg.mid(27,2)+ msg.mid(24,2);
    QString str6 = msg.mid(33,2)+ msg.mid(30,2);
    QString str7 = msg.mid(39,2)+ msg.mid(36,2);
    QString str8 = msg.mid(45,2)+ msg.mid(42,2);
    QString str9 = msg.mid(51,2)+ msg.mid(48,2);
    QString str10 = msg.mid(57,2)+ msg.mid(54,2);

    QString checkStr = msg.mid(63,2) + msg.mid(60,2);
    int checkNum = checkStr.toInt(NULL,16);

    int data[10] ;
    data[0] = str1.toInt(NULL,16);
    data[1] = str2.toInt(NULL,16);
    data[2] = str3.toInt(NULL,16);
    data[3] = str4.toInt(NULL,16);
    data[4] = str5.toInt(NULL,16);
    data[5] = str6.toInt(NULL,16);
    data[6] = str7.toInt(NULL,16);
    data[7] = str8.toInt(NULL,16);
    data[8] = str9.toInt(NULL,16);
    data[9] = str10.toInt(NULL,16);

    int checksum_32 = 0;
    for(int i=0; i<10; i++)
        checksum_32 = (checksum_32<<1) + data[i];

    int result;
    result = (checksum_32>>15) + (checksum_32 & 0x7FFF);
    result = result & 0x7FFF;
//    qDebug()<<" result = "<<result<<endl;

    if(result == checkNum)
        return true;
    else
        return false;


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
            if(dirPath.isEmpty())
            {
                QMessageBox::information(NULL,"warn","the Dir is empty,please check!");
            }else
            {
//                isDirExist(dirPath);
                emit createDirSignal(dirPath);
            }

        }
//        fullDirPath = dirPath;
        isSaveFlag = true;
    }

    isSaveFlag = isSave;

}



