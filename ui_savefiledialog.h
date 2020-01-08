/********************************************************************************
** Form generated from reading UI file 'savefiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEFILEDIALOG_H
#define UI_SAVEFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saveFileDialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *SelFilePath_pushButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *showNum_lineEdit;

    void setupUi(QDialog *saveFileDialog)
    {
        if (saveFileDialog->objectName().isEmpty())
            saveFileDialog->setObjectName(QStringLiteral("saveFileDialog"));
        saveFileDialog->resize(511, 449);
        QIcon icon;
        icon.addFile(QStringLiteral("icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveFileDialog->setWindowIcon(icon);
        groupBox = new QGroupBox(saveFileDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 40, 451, 111));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(11, 33, 107, 16));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(12, 64, 47, 16));
        radioButton_2->setMaximumSize(QSize(50, 16777215));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(68, 60, 361, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        SelFilePath_pushButton = new QPushButton(layoutWidget);
        SelFilePath_pushButton->setObjectName(QStringLiteral("SelFilePath_pushButton"));
        SelFilePath_pushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(SelFilePath_pushButton);

        pushButton = new QPushButton(saveFileDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 380, 75, 23));
        pushButton_2 = new QPushButton(saveFileDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 380, 75, 23));
        groupBox_2 = new QGroupBox(saveFileDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 160, 451, 121));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(70, 30, 213, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        showNum_lineEdit = new QLineEdit(layoutWidget1);
        showNum_lineEdit->setObjectName(QStringLiteral("showNum_lineEdit"));

        horizontalLayout_2->addWidget(showNum_lineEdit);


        retranslateUi(saveFileDialog);

        QMetaObject::connectSlotsByName(saveFileDialog);
    } // setupUi

    void retranslateUi(QDialog *saveFileDialog)
    {
        saveFileDialog->setWindowTitle(QApplication::translate("saveFileDialog", "\345\212\237\350\203\275\350\256\276\347\275\256\347\225\214\351\235\242", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("saveFileDialog", "\346\226\207\344\273\266\344\277\235\345\255\230\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        radioButton->setText(QApplication::translate("saveFileDialog", "\344\270\215\344\277\235\345\255\230\357\274\210\347\274\272\347\234\201\357\274\211", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("saveFileDialog", "\344\277\235\345\255\230", Q_NULLPTR));
        label->setText(QApplication::translate("saveFileDialog", "\345\255\230\345\202\250\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        SelFilePath_pushButton->setText(QApplication::translate("saveFileDialog", "...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("saveFileDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("saveFileDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("saveFileDialog", "\346\230\276\347\244\272\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("saveFileDialog", "     \346\230\276\347\244\272\345\234\206\345\221\250\346\225\260\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class saveFileDialog: public Ui_saveFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEFILEDIALOG_H
