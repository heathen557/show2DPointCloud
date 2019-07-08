#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <QDialog>
#include"globaldata.h"

namespace Ui {
class saveFileDialog;
}

class saveFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveFileDialog(QWidget *parent = 0);
    ~saveFileDialog();

    QString file_path;
    int showCircleNum;  //显示多少圈
    int showRadiusMeter;   //显示半径为多少米


private slots:
    void on_SelFilePath_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

 signals:
    void saveSubmitSignal(bool isSave,int circleNum,int radiusMeter);


private:
    Ui::saveFileDialog *ui;
};

#endif // SAVEFILEDIALOG_H
