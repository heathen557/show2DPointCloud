﻿#include "receserial_msg.h"


extern Settings currentSettings;

extern vector<vector<float>> AllPoint_vec;
extern QMutex m_mutex;

receSerial_msg::receSerial_msg(QObject *parent) : QObject(parent)
{
    qDebug()<<" the thread begin "<<endl;
    firstAngle = 0;
    receRotation = 0;
    serial = NULL;

    showCircleNum = 2;
    saveFileIndex = 0;
    isSaveFlag = false;
}

void receSerial_msg::openOrCloseSerial_slot(bool flag)
{
    if(NULL == serial)
    {
        serial = new QSerialPort(this);
        connect(serial, SIGNAL(readyRead()), this, SLOT(readDataSlot()),Qt::DirectConnection);
    }

    if(true == flag)   //打开串口
    {
        serial->setPortName(currentSettings.name);
        serial->setBaudRate(currentSettings.baudRate);
        serial->setDataBits(currentSettings.dataBits);
        serial->setParity(currentSettings.parity);
        serial->setStopBits(currentSettings.stopBits);
        serial->setFlowControl(currentSettings.flowControl);
        if(serial->open(QIODevice::ReadWrite))
        {
            qDebug()<<"serial open success!!";
            emit returnLinkInfo_signal("open",true);
        }else{
            qDebug()<<"serial open error";
            emit returnLinkInfo_signal("open",false);
        }
    }else              //关闭串口
    {
        serial->close();
        qDebug()<<"serial close success!";
        emit returnLinkInfo_signal("close",true);
        m_buffer.clear();
    }

}


//!
//! \brief receSerial_msg::readDataSlot  串口接收数据，并对命令进行解析 （暂时约定传输数据为小端模式）
//!   1、首先接收到字符串 以后把它转换成16进制的字符串类型，本次处理时去掉空格；
//!   2、将接收到的数据添加到成员变量m_buffer中；
//!   3、根据长度字段将单个命令提取出来
//!   4、对单个命令进行解析
//!   5、命令解析完毕后，从m_buffer中剔除到这个命令，并更新totallen
void receSerial_msg::readDataSlot()
{
    QByteArray temp = serial->readAll();
    QString strHex;//16进制数据

    int singleLen = 10*2;   //一包数据10个字节

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

//        qDebug()<<"m_buffer = "<<m_buffer;
//        return;

        int totallen = m_buffer.size();
        while(totallen)
        {
            if(totallen <singleLen)    //一个报文至少要有44个字节
                return;

           int indexOf5A = m_buffer.indexOf("5A83",0);
           if(indexOf5A < 0)  //没有找到5A
           {
               qDebug()<<QString::fromUtf8("msg maybe error,can't find FA")<<"index ="<<indexOf5A<<"buffer"<<m_buffer<<endl;
               return;
           }else if(indexOf5A>0)  //第一次的时候前面会有冗余数据，删掉
           {
               m_buffer = m_buffer.right(totallen-indexOf5A);
               totallen = m_buffer.size();
//               qDebug()<<"the first msg ,has some Redundant data,  indexOf5A="<<indexOf5A<<"  the left msg = "<<m_buffer<<endl;
               if(totallen <singleLen)
                   return;
           }

           QString lenStr= m_buffer.mid(6,2) + m_buffer.mid(4,2);
           int dataLen = lenStr.toInt(NULL,16) * 2;
           int len = dataLen + 5*2;



           float pointNum = (lenStr.toInt(NULL,16) - 6)/3;  //一包有多少个点

//           qDebug()<<"dataLen ="<<dataLen/2<<"   pointNum="<<pointNum;

           if(totallen<len)
               return;


           //以下数据为FA打头数据
           //进行校验的操作
           QString single_Data = m_buffer.left(len);     //一帧数据
//           qDebug()<<"singleData = "<<single_Data;

           if(!msgCheck(single_Data))
           {
               qDebug()<<"msgCheck error!  single_Data ="<< single_Data <<endl;
               m_buffer = m_buffer.right(totallen - 2);
               totallen = m_buffer.size();
               return;
           }



           // 1、转速
           QString RotationSpeed_str = single_Data.mid(10,2) + single_Data.mid(8,2);
           float tmpRotation_ = RotationSpeed_str.toInt(NULL,16);
           receRotation = tmpRotation_ / 100.0;         //实际值扩大100倍



           //2、起始角度
           QString firstAngStr = single_Data.mid(14,2) + single_Data.mid(12,2);
           float firstAngfloat = firstAngStr.toInt(NULL,16);
           firstAngle = firstAngfloat/100.0;
           // 3 角度分辨率
//           float angle_offset = receRotation*360.0/100.0/4800.0;


           //3、结束角度
           QString endAngleStr =  single_Data.mid(18,2) + single_Data.mid(16,2);
           float endAnglefloat = endAngleStr.toInt(NULL,16);
           endAngle = endAnglefloat/100.0;

           if((0 ==int(endAngle)) && endAngle<firstAngle)
               endAngle = 360.0;

           // 4、角度分辨率
           float angle_oneOffset = (endAngle - firstAngle)/pointNum;


//           qDebug()<<"receRotation = "<<receRotation<<"   firstAngle="<<firstAngle<<"  endAngle="<<endAngle<<"  angle_offset="<<angle_oneOffset;
           //4、一包数据包含了6个点的数据、
           QString distanceStr;
           QString peakStr;
           float angleTmp;
           int distanceInt;
           int package = pointNum;
           for(int j=0; j<package; j++)
           {
               angleTmp = firstAngle + j*angle_oneOffset;
               distanceStr = single_Data.mid(20+6*j+2,2 ) + single_Data.mid(20+6*j+0,2);
               distanceInt = distanceStr.toInt(NULL,16);

               peakStr = single_Data.mid(20+6*j+4,2) ;

               Rece_points.push_back(angleTmp);
               Rece_points.push_back(distanceInt);
//               Rece_points.push_back(3000);

//               qDebug()<<"angleTmp = "<<angleTmp<<"    distance ="<<distanceInt;



           }
//           QString saveData = single_Data+"  "+ QString::number(firstAngle) +"  " ;






//           //报文顺序标识 0xA0-0xF9:  0xA0: 0,1,2,3
//           int index = single_Data.mid(2,2).toInt(NULL,16);
//           if(index<160 || index>249)
//           {
//               qDebug()<<"index beyond the tolence,the dataAnalye mayebe error ,index = "<< index<<"  single_Data"<<  single_Data <<endl;
//               m_buffer = m_buffer.right(totallen - 2);
//               totallen = m_buffer.size();
//               return;
//           }
//           firstAngle = (index-160)*4;        //每一组的第一个点对应的角度  1度的分辨率

//           //转速：2bytes 04 00
//           QString RotationSpeed_str = single_Data.mid(6,2) + single_Data.mid(4,2);
//           float tmpRotation_ = RotationSpeed_str.toInt(NULL,16);
//           receRotation = tmpRotation_ / 100.0;         //实际值扩大100倍

//           //一个包存储了16个点的数据
//           QString distanceStr;
//           int distanceInt;
//           float angleTmp = firstAngle;
//           distanceStr = single_Data.mid(8+2,2) + single_Data.mid(8,2);
//           int distanceInt_1 =  distanceStr.toInt(NULL,16);
//           for(int i=0; i<64; i+=4)
//           {
//               distanceStr = single_Data.mid(8+i+2,2) + single_Data.mid(8+i,2);
//               distanceInt = distanceStr.toInt(NULL,16);
//               Rece_points.push_back(angleTmp);
//               Rece_points.push_back(distanceInt);
//               angleTmp += 0.25;       //每个点相邻0.25度
//           }

//            qDebug()<<" singleData = "<<single_Data<<"firstAngle = "<<firstAngle<<"  distanceInt_1="<<distanceInt_1<<endl;
//            QString saveData = single_Data+"  "+ QString::number(firstAngle) +"  " + QString::number(distanceInt_1)  ;


//            //生成数据文件
//            if(true == isSaveFlag  && saveCircleNum >= 3)
//            {
//               saveFileIndex++;
//               saveCircleNum = 5;  //设置为一个大于3的数字即可
//               emit writeLogSignal(saveData,saveFileIndex);
//            }

           if(360 == int(endAngle) && (!Rece_points.empty()) )  //360度已经接收完毕
           {
               saveCircleNum++;
               emit sendRotateSpeed_signal(1,receRotation);   //一圈发送一次

               m_mutex.lock();
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
               m_mutex.unlock();



               //生成数据文件
               if(true == isSaveFlag  && saveCircleNum >= 3)
               {
                  saveFileIndex++;
                  saveCircleNum = 5;  //设置为一个大于3的数字即可
                  emit writeLogSignal(saveData,saveFileIndex);
               }
               saveData.clear();

           }

           saveData.append(single_Data).append("\n");

           m_buffer = m_buffer.right(totallen - len);
           totallen = m_buffer.size();


           lastAngle = firstAngle;
        }
    }
}



//字节校验 从第二个字节开始，到倒数第二个字节 求和并取反 判断是否与最后一个字节相等
bool receSerial_msg::msgCheck(QString msg)
{
//    QString strCmd = msg;
//    strCmd = strCmd.replace(" ","");
//    int len = strCmd.length();

//    int sunNum = 0;
//    int i=0;
//    for(i=0; i<len-4; i+=2)
//    {
//        sunNum += strCmd.mid(i,2).toInt(NULL,16);
//    }

//    QString checkStr = strCmd.mid(i+2,2) + strCmd.mid(i,2);
//    int checkNum = checkStr.toInt(NULL,16);

//    if(sunNum == checkNum)
//    {
//        return true;
//    }else
//    {
//        return false;
//    }

    QString strCmd = msg;
    strCmd = strCmd.replace(" ","");
    int len = strCmd.length();
    int i=2;
    int num = 0;
    for(;i<len-2;i+=2)
    {
        num += msg.mid(i,2).toInt(NULL,16);
    }

    int checkNum = msg.mid(i,2).toInt(NULL,16);
    if(quint8(~num) == checkNum)
    {
        return true;
    }else
    {
        return false;
    }

}


//!
//! \brief receSerial_msg::sendSerialSlot
//! \param sendCmdStr: 不带校验位的 QString 类型的字符串  QString cmdStr = "5A 03 04 00 0A 00 88 13 ";
//! 1、添加校验位
//! 2、转换为字节数,存储在QByteArray
//! 3、向串口发送数据
//! 4、清空缓存区
void receSerial_msg::sendSerialSlot(QByteArray sendCmdStr)
{

    if(serial->isWritable())
    {
        serial->write(sendCmdStr);            //串口发送字节数据
        serial->flush();                     //清空缓冲区
        qDebug()<<"send msg = "<<sendCmdStr;
    }
    else
    {
        qDebug()<<"can not write right now ";
    }

}


