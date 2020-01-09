#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include<QString>
#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<qmutex.h>
#include<vector>
#include<iostream>
#include<math.h>
#include<QTimer>
using namespace std;



struct Settings {
    QString name;
    qint32 baudRate;
    QString stringBaudRate;
    QSerialPort::DataBits dataBits;
    QString stringDataBits;
    QSerialPort::Parity parity;
    QString stringParity;
    QSerialPort::StopBits stopBits;
    QString stringStopBits;
    QSerialPort::FlowControl flowControl;
    QString stringFlowControl;
    bool localEchoEnabled;
};


enum DiskspaceFlag
{
	NoSpace,
	HaveSpace
};
class globaldata
{
public:
	static int set_listening_flag;
	static QString current_path;
	static QString default_save_path;
	static QString strCssContent;
	static int client_flag;
	static int diskspace_flag;
	static QString connectionUI;
	static QString connectionwork1;
    static QString showfileinfo_conndb;
	static int LogCount;
	static QString oldLogFile;
};

#endif 
