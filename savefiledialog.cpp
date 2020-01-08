#include "savefiledialog.h"
#include "ui_savefiledialog.h"
#include "QFileDialog"
#include"QDebug"


saveFileDialog::saveFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveFileDialog)
{
        ui->setupUi(this);

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

       showCircleNum = line[2].toInt();
//       int saveFlag = line[3].toInt();
//       file_path = line[4];
//       showRadiusMeter = line[5].toInt();

       ui->radioButton->setChecked(true);
       ui->lineEdit->setEnabled(false);
       ui->SelFilePath_pushButton->setEnabled(false);
//       if(0 == saveFlag)   //不保存成文件
//       {

//       }else        //保存成文件
//       {
//           ui->lineEdit->setEnabled(true);
//           ui->SelFilePath_pushButton->setEnabled(true);
//           ui->radioButton_2->setChecked(true);

//           emit saveSubmitSignal(true,showCircleNum,showRadiusMeter);
//       }


//    file_path = QCoreApplication::applicationDirPath();
//     qDebug()<<" file_path ="<<file_path<<endl;
      ui->showNum_lineEdit->setText(line[2]);
//      ui->lineEdit->setText(file_path);


}

saveFileDialog::~saveFileDialog()
{
    delete ui;
}

//@brief:不保存
void saveFileDialog::on_radioButton_clicked()
{
    ui->SelFilePath_pushButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}

//@brief:保存
void saveFileDialog::on_radioButton_2_clicked()
{
    ui->SelFilePath_pushButton->setEnabled(true);
    ui->lineEdit->setEnabled(true);
}

//@brief:选择路径
void saveFileDialog::on_SelFilePath_pushButton_clicked()
{
    file_path = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...","./");
    if(file_path.isEmpty())
    {
       qDebug()<<"没有选择路径"<<endl;
        return;
    }
    else
    {
        qDebug() << file_path << endl;
        ui->lineEdit->setText(file_path);
    }
}


//确认提交
void saveFileDialog::on_pushButton_clicked()
{
    int checkFlag;
    int showNum = ui->showNum_lineEdit->text().toInt();
    int showRadius= 0;
    if(ui->radioButton_2->isChecked())
    {
        qDebug()<<"saveFileDialog has check the fileSave,file_path = "<<file_path<<endl;
        checkFlag = 1;
        emit saveSubmitSignal(true,showNum,showRadius);
    }else
    {
        checkFlag = 0;
        emit saveSubmitSignal(false,showNum,showRadius);
    }

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

    if(file.open(QIODevice::WriteOnly))
    {
        QByteArray writeData;
        writeData = line[0].toLatin1()+ temp + line[1].toLatin1()+temp+\
                QString::number(showNum).toLatin1() ;
        if (-1 == file.write(writeData))
        {
            qDebug()<<"ERROR";
        }
        file.close();
    }


    this->hide();
}

//取消
void saveFileDialog::on_pushButton_2_clicked()
{
    this->hide();
}
