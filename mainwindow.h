#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include <QtSerialPort/QSerialPort>
#include<QTimer>
#include<settingdialog.h>
#include<savefiledialog.h>
#include<savelocalfile.h>
#include"receserial_msg.h"
#include<QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    settingDialog *setDia;
    saveFileDialog saveDia;

    QTimer myReadTimer;
    QString m_buffer;
    int lastAngleInt;         //保存上次的角度，方便判断是否一圈结束
    QTimer transTimer;
    int numOfCircle;          //接收圈数
    bool isSaveFlag;
    int dirCurIndex;        //一天当中的文件夹标识 2016-06-28_1
    QString fullDirPath;
    int saveCircleNum;      //log中显示的圈数
    int showCircleNum;

    int saveFileIndex;

    int firstAngle;

    saveLocalFile *saveLocalDia;
    QThread *saveThread;

    float receRotation;     //协议中携带的转速


    receSerial_msg *receSerial_obj;
    QThread *receSeri_thread;

    bool isSerialOpenFlag;



public slots:
    void showSettingDialog();   //串口设置界面

    void seriOpen_slot(bool);       //打开串口
    void closeConnect();        //关闭串口
    void transCheckSlot();      //获取传输速率
    void showSaveFileDialog();  //文件保存设置界面

    void saveSubmitSlot(bool isSave,int circleNum, int radiusMeter);  //接收是否保存命令

    void sendRotateSpeed_slot(float,float);

    void returnLinkInfo_slot(QString,bool);   //串口连接的返回信息

signals:
    void createDirSignal(QString);
    void writeLogSignal(QString,int);

    void seriOpen_signal(bool);
    void sendSerialSignal(QByteArray);   //串口发送数据

private slots:
    void on_startRotate_pushButton_clicked();
};

#endif // MAINWINDOW_H
