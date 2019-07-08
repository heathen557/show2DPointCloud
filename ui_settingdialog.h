/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_settingDialog
{
public:
    QGroupBox *gbox1;
    QLabel *label;
    QComboBox *serialPortInfoListBox;
    QComboBox *baudRateBox;
    QLabel *label_2;
    QComboBox *dataBitsBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *parityBox;
    QComboBox *stopBitsBox;
    QPushButton *btnOpen;

    void setupUi(QDialog *settingDialog)
    {
        if (settingDialog->objectName().isEmpty())
            settingDialog->setObjectName(QStringLiteral("settingDialog"));
        settingDialog->resize(256, 287);
        gbox1 = new QGroupBox(settingDialog);
        gbox1->setObjectName(QStringLiteral("gbox1"));
        gbox1->setGeometry(QRect(40, 30, 171, 211));
        label = new QLabel(gbox1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 54, 12));
        serialPortInfoListBox = new QComboBox(gbox1);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));
        serialPortInfoListBox->setGeometry(QRect(60, 20, 91, 22));
        baudRateBox = new QComboBox(gbox1);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));
        baudRateBox->setGeometry(QRect(60, 50, 91, 22));
        label_2 = new QLabel(gbox1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 54, 12));
        dataBitsBox = new QComboBox(gbox1);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));
        dataBitsBox->setGeometry(QRect(60, 80, 91, 22));
        label_3 = new QLabel(gbox1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 54, 12));
        label_4 = new QLabel(gbox1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 54, 12));
        label_5 = new QLabel(gbox1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 150, 54, 12));
        parityBox = new QComboBox(gbox1);
        parityBox->setObjectName(QStringLiteral("parityBox"));
        parityBox->setGeometry(QRect(60, 110, 91, 22));
        stopBitsBox = new QComboBox(gbox1);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));
        stopBitsBox->setGeometry(QRect(60, 140, 91, 22));
        btnOpen = new QPushButton(gbox1);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setGeometry(QRect(20, 170, 131, 31));
        btnOpen->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(settingDialog);

        QMetaObject::connectSlotsByName(settingDialog);
    } // setupUi

    void retranslateUi(QDialog *settingDialog)
    {
        settingDialog->setWindowTitle(QApplication::translate("settingDialog", "Dialog", Q_NULLPTR));
        gbox1->setTitle(QApplication::translate("settingDialog", "\344\270\262\345\217\243\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("settingDialog", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("settingDialog", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("settingDialog", "\346\225\260\346\215\256\344\275\215\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("settingDialog", "\346\240\241\351\252\214\344\275\215\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("settingDialog", "\345\201\234\346\255\242\344\275\215\357\274\232", Q_NULLPTR));
        btnOpen->setText(QApplication::translate("settingDialog", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settingDialog: public Ui_settingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
