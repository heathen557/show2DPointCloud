#include "savelocalfile.h"
#include<QDebug>
#include<QDir>

saveLocalFile::saveLocalFile(QObject *parent) : QObject(parent)
{
    qDebug()<<"the save local file has come in "<<endl;
}



//@brief:判断文件夹是否存在,不存在则创建
bool saveLocalFile::isDirExist(QString fullPath) //判断文件夹是否存在,不存在则创建
{
    if(fullPath.isEmpty())
        qDebug()<<"isDirExist function: the fullPath is Empty "<<endl;

    qDebug()<<"going to jduge the dir = "<<fullPath<<endl;
    QDir dir(fullPath);
    if(dir.exists())
    {
      qDebug()<<fullPath<<"dir already exists, dir = "<<fullPath<<endl;
      dirCurIndex++;
      fullDirPath = fullPath + "_1";
      isDirExist(fullDirPath);
      return true;
    }
    else
    {
       qDebug()<<"it will create the dir,the dir= "<<fullPath<<endl;
       fullDirPath = fullPath;
       dirCurIndex = 0;
       bool ok = dir.mkdir(fullDirPath);//只创建一级子目录，即必须保证上级目录存在
       return ok;
    }
}


//按照标识写文件
// input:text:写入文本的内容
// numOfFile：第几个文件
void saveLocalFile::writeLog(QString text,int numOfFile)
{
    QString sFilePath=fullDirPath + "/"+QString::number(numOfFile)+".txt";
    QFile file(sFilePath);
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);

    QTextStream out(&file);
    out<<text.toLocal8Bit()<<endl;
    file.close();
}
