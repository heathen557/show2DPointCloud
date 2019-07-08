#include "settingdialog.h"
#include "ui_settingdialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QFile>

settingDialog::settingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingDialog)
{
    ui->setupUi(this);


    seriaPort_init();


}

void settingDialog::seriaPort_init()
{
    QFile file("setting.ini");
    QByteArray temp("\r\n");
    QString line[20];

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        int i = 0;
        while (!in.atEnd())
        {
            line[i] = in.readLine();
            i++;
        }
        file.close();
    }
    int numSeri_ = line[0].toInt();
    int baudRateBox_ = line[1].toInt();

    QStringList comList;//串口号
    comList.clear();
    comList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
            <<"COM7"<<"COM8"<<"COM9"<<"COM10"<<"COM11"<<"COM12"
            <<"COM13"<<"COM14"<<"COM15"<<"COM16"<<"COM17"<<"COM18"
            <<"COM19"<<"COM20"<<"COM21"<<"COM22"<<"COM23"<<"COM24"
            <<"COM25"<<"COM26"<<"COM27"<<"COM28"<<"COM28"<<"COM29"<<"COM30";
    ui->serialPortInfoListBox->clear();
    ui->serialPortInfoListBox->addItems(comList);
    ui->serialPortInfoListBox->setCurrentIndex(numSeri_);

    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateBox->addItem(QStringLiteral("256000"), QSerialPort::Baud256000);
    ui->baudRateBox->addItem(tr("Custom"));
    ui->baudRateBox->setCurrentIndex(baudRateBox_);

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

settingDialog::~settingDialog()
{
    delete ui;
}

void settingDialog::on_btnOpen_clicked()
{
//    if(ui->btnOpen->text() == "打开串口")
    {
        currentSettings.name = ui->serialPortInfoListBox->currentText();

        if (ui->baudRateBox->currentIndex() == 4) {
            currentSettings.baudRate = ui->baudRateBox->currentText().toInt();
        } else {
            currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                        ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
        }
        currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

        currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                    ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
        currentSettings.stringDataBits = ui->dataBitsBox->currentText();

        currentSettings.parity = static_cast<QSerialPort::Parity>(
                    ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
        currentSettings.stringParity = ui->parityBox->currentText();

        currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                    ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
        currentSettings.stringStopBits = ui->stopBitsBox->currentText();

//        serial->setPortName(currentSettings.name);
//        serial->setBaudRate(currentSettings.baudRate);
//        serial->setDataBits(currentSettings.dataBits);
//        serial->setParity(currentSettings.parity);
//        serial->setStopBits(currentSettings.stopBits);
//        serial->setFlowControl(currentSettings.flowControl);
//        if (serial->open(QIODevice::ReadWrite)) {
//        } else {
//            QMessageBox::critical(this, tr("Error"), serial->errorString());
//        }


//        ui->widget->timer.start(5);
//        transTimer.start(1000);
         qDebug()<<"name="<<currentSettings.name<<" baudRate ="<<currentSettings.baudRate<<" dataBits="<<currentSettings.dataBits<<" parity="<<currentSettings.parity<<" stopBits="<<currentSettings.stopBits<<" flowCon"<<currentSettings.flowControl;

//         ui->labIsOpen->setText("串口状态：打开");
//         ui->label_show_2->setText("5 ms ");

         emit seriOpen_signal();
//         ui->btnOpen->setText("关闭串口");

         QFile file("setting.ini");
         QByteArray temp("\r\n");
         QString line[20];

         if (file.open(QIODevice::ReadOnly))
         {
             QTextStream in(&file);
             int i = 0;
             while (!in.atEnd())
             {
                 line[i] = in.readLine();
                 i++;
             }
             file.close();
         }

         int seriNum = ui->serialPortInfoListBox->currentIndex();
         int baudBox = ui->baudRateBox->currentIndex();


         if(file.open(QIODevice::WriteOnly))
         {
             QByteArray writeData;
             writeData = QString::number(seriNum).toLatin1()+ temp + QString::number(baudBox).toLatin1()+temp+\
                     line[2].toLatin1()+ temp +line[3].toLatin1()+ temp+ line[4].toLatin1()+ temp +line[5].toLatin1();
             if (-1 == file.write(writeData))
             {
                 qDebug()<<"ERROR";
             }
             file.close();
         }

        int saveInt = line[3].toInt();
        bool saveFlag ;
        if(1 == saveInt)
        {
            saveFlag = true;
        }else
        {
            saveFlag = false;
        }
        int showCircleNum = line[2].toInt();
        int showRadiusMeter = line[5].toInt();

        saveSubmitSignal(saveFlag,showCircleNum,showRadiusMeter);


    }
//    else
    {
//        serial->close();
//        ui->widget->timer.stop();
//        transTimer.stop();
//        ui->labIsOpen->setText("串口状态：关闭");
//        ui->label_show_1->setText("0 bps");
//        ui->label_show_2->setText("0 ms ");
//        AllPoint_vec.clear();
//        ui->btnOpen->setText("打开串口");
    }
}
