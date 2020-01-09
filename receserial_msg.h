#ifndef RECESERIAL_MSG_H
#define RECESERIAL_MSG_H

#include <QObject>
#include<QDebug>
#include<QDataStream>
#include<vector>
#include<QTimer>
#include<QList>
#include<globaldata.h>

using namespace std;





class receSerial_msg : public QObject
{
    Q_OBJECT
public:
    explicit receSerial_msg(QObject *parent = 0);

    QSerialPort *serial;

    QByteArray m_buffer;

    int firstAngle;

    float receRotation;

    int saveCircleNum;

    int saveFileIndex;

    int numOfCircle;

    bool isSaveFlag;

    int showCircleNum;

    vector<float> Rece_points;




signals:
    void dealedData_signal(QString,vector<double>,vector<double>);     //当前的tof值 ; plotData ; statisticData

    void showResultMsg_signal(QStringList);  //显示tof peak相关  主界面显示;  主线程中设定一个暂存变量，每秒钟在result窗口中显示append(),然后清空result

    void returnLinkInfo_signal(QString, bool);

    void writeLogSignal(QString,int);

    void sendRotateSpeed_signal(float,float);



public slots:
    void readDataSlot();

    bool msgCheck(QString msg);

    void openOrCloseSerial_slot(bool);

    void sendSerialSlot(QByteArray);              //串口发送数据的槽函数

    QString addCheck(QString);

};

#endif // RECESERIAL_MSG_H
