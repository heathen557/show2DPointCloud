#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include <QtSerialPort/QSerialPort>
#include<QTimer>
#include<settingdialog.h>
#include<savefiledialog.h>
#include<savelocalfile.h>
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
    QSerialPort *serial;
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

    int firstAngle;
    int secondAngle;
    int thirdAngle;
    int fourAngle;

    saveLocalFile *saveLocalDia;
    QThread *saveThread;


public slots:
    void showSettingDialog();   //串口设置界面
    void readData();            //读取串口数据
    void seriOpen_slot();       //打开串口
    void closeConnect();        //关闭串口
    void transCheckSlot();      //获取传输速率
    void showSaveFileDialog();  //文件保存设置界面

    void saveSubmitSlot(bool isSave,int circleNum, int radiusMeter);  //接收是否保存命令
    bool msgCheck(QString msg);  //和校验
    int findComplement(int num);  //二进制取反

signals:
    void createDirSignal(QString);
    void writeLogSignal(QString,int);

};

#endif // MAINWINDOW_H
