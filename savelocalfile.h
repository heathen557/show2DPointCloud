#ifndef SAVELOCALFILE_H
#define SAVELOCALFILE_H

#include <QObject>

class saveLocalFile : public QObject
{
    Q_OBJECT
public:
    explicit saveLocalFile(QObject *parent = 0);

    int dirCurIndex;
    QString fullDirPath;

signals:

public slots:
    bool isDirExist(QString fullPath);  //判断文件夹是否存在,不存在则创建
    void writeLog(QString text,int numOfFile);
};

#endif // SAVELOCALFILE_H
