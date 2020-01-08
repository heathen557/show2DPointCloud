/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GLWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *showlabel_2;
    QLabel *label_3;
    QLabel *Rotation_label;
    QSpacerItem *horizontalSpacer;
    QPushButton *startRotate_pushButton;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(818, 729);
        QIcon icon;
        icon.addFile(QStringLiteral("icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("images/ccAlign.png"), QSize(), QIcon::Normal, QIcon::Off);
        action->setIcon(icon1);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("images/ccDelete.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_2->setIcon(icon2);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("images/ccGear.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_3->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(800, 600));
        widget->setMaximumSize(QSize(3000, 3000));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        showlabel_2 = new QLabel(centralWidget);
        showlabel_2->setObjectName(QStringLiteral("showlabel_2"));
        showlabel_2->setMinimumSize(QSize(50, 20));

        horizontalLayout->addWidget(showlabel_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        Rotation_label = new QLabel(centralWidget);
        Rotation_label->setObjectName(QStringLiteral("Rotation_label"));

        horizontalLayout->addWidget(Rotation_label);

        horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        startRotate_pushButton = new QPushButton(centralWidget);
        startRotate_pushButton->setObjectName(QStringLiteral("startRotate_pushButton"));

        horizontalLayout->addWidget(startRotate_pushButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 818, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(action_3);
        mainToolBar->addAction(action);
        mainToolBar->addAction(action_2);
        mainToolBar->addAction(action_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\212\257\350\247\206\347\225\214\345\215\225\347\202\271\346\250\241\347\273\204\350\260\203\350\257\225\350\275\257\344\273\266", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\345\273\272\347\253\213\350\277\236\346\216\245", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\345\212\237\350\203\275\350\256\276\347\275\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\275\254\351\200\237\357\274\232", Q_NULLPTR));
        showlabel_2->setText(QApplication::translate("MainWindow", "0 R/s", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\347\220\206\350\256\272\350\275\254\351\200\237\357\274\232", Q_NULLPTR));
        Rotation_label->setText(QApplication::translate("MainWindow", "0 R/s", Q_NULLPTR));
        startRotate_pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\227\213\350\275\254", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275\351\200\211\351\241\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
