#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

#include<QMessageBox>
#include<QDebug>
#include<QFile>
#include<globaldata.h>

namespace Ui {
class settingDialog;
}

class settingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingDialog(QWidget *parent = 0);
    ~settingDialog();
    void seriaPort_init();


private slots:
    void on_btnOpen_clicked();

private:
    Ui::settingDialog *ui;


signals:
    void seriOpen_signal(bool );
    void saveSubmitSignal(bool isSave,int circleNum,int radiusMeter);

};

#endif // SETTINGDIALOG_H
