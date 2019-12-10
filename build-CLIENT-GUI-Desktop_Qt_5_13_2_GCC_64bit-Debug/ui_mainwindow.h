/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_IP_Adress;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_Port_No;
    QPushButton *pushButton_Connect;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_Display_PATH;
    QPushButton *pushButton_Send;
    QGraphicsView *imageView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(959, 560);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 232, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_IP_Adress = new QLineEdit(layoutWidget);
        lineEdit_IP_Adress->setObjectName(QString::fromUtf8("lineEdit_IP_Adress"));

        horizontalLayout_2->addWidget(lineEdit_IP_Adress);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_Port_No = new QLineEdit(layoutWidget);
        lineEdit_Port_No->setObjectName(QString::fromUtf8("lineEdit_Port_No"));

        horizontalLayout_3->addWidget(lineEdit_Port_No);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton_Connect = new QPushButton(layoutWidget);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));

        verticalLayout->addWidget(pushButton_Connect);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_Display_PATH = new QLineEdit(layoutWidget);
        lineEdit_Display_PATH->setObjectName(QString::fromUtf8("lineEdit_Display_PATH"));

        horizontalLayout_4->addWidget(lineEdit_Display_PATH);

        pushButton_Send = new QPushButton(layoutWidget);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));

        horizontalLayout_4->addWidget(pushButton_Send);


        verticalLayout_2->addLayout(horizontalLayout_4);

        imageView = new QGraphicsView(centralwidget);
        imageView->setObjectName(QString::fromUtf8("imageView"));
        imageView->setGeometry(QRect(250, 20, 701, 501));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 959, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port No.", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("MainWindow", "Connect to Server", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
