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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    GLWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *showlabel_1;
    QLabel *label_2;
    QLabel *showlabel_2;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(824, 703);
        QIcon icon;
        icon.addFile(QStringLiteral("icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(800, 600));
        widget->setMaximumSize(QSize(600, 600));

        formLayout->setWidget(0, QFormLayout::LabelRole, widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        showlabel_1 = new QLabel(centralWidget);
        showlabel_1->setObjectName(QStringLiteral("showlabel_1"));
        showlabel_1->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(showlabel_1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        showlabel_2 = new QLabel(centralWidget);
        showlabel_2->setObjectName(QStringLiteral("showlabel_2"));
        showlabel_2->setMinimumSize(QSize(50, 20));

        horizontalLayout->addWidget(showlabel_2);

        horizontalSpacer = new QSpacerItem(478, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 824, 23));
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

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\212\257\350\247\206\347\225\214\344\270\262\345\217\243\346\225\260\346\215\256\350\260\203\350\257\225\350\275\257\344\273\266", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\345\273\272\347\253\213\350\277\236\346\216\245", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\345\212\237\350\203\275\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\270\247\347\216\207\357\274\232", Q_NULLPTR));
        showlabel_1->setText(QApplication::translate("MainWindow", "0 f/s", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\275\254\351\200\237\357\274\232", Q_NULLPTR));
        showlabel_2->setText(QApplication::translate("MainWindow", "0 R/s", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
