/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QPushButton *loginButton;
    QLabel *profileLabel;
    QPushButton *returnButton;
    QPushButton *addFriendButton;
    QLabel *postsLabel;
    QTableWidget *friendsTable;
    QTableWidget *suggestedTable;
    QLabel *postsIndicator;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loginLabel = new QLabel(centralwidget);
        loginLabel->setObjectName("loginLabel");
        loginLabel->setGeometry(QRect(50, 20, 271, 21));
        loginLineEdit = new QLineEdit(centralwidget);
        loginLineEdit->setObjectName("loginLineEdit");
        loginLineEdit->setGeometry(QRect(50, 50, 141, 31));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(50, 90, 100, 32));
        profileLabel = new QLabel(centralwidget);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setGeometry(QRect(20, 20, 141, 21));
        returnButton = new QPushButton(centralwidget);
        returnButton->setObjectName("returnButton");
        returnButton->setGeometry(QRect(230, 10, 191, 32));
        addFriendButton = new QPushButton(centralwidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(440, 10, 191, 32));
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(300, 90, 971, 241));
        postsLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        friendsTable = new QTableWidget(centralwidget);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(20, 50, 271, 192));
        suggestedTable = new QTableWidget(centralwidget);
        suggestedTable->setObjectName("suggestedTable");
        suggestedTable->setGeometry(QRect(20, 250, 271, 192));
        postsIndicator = new QLabel(centralwidget);
        postsIndicator->setObjectName("postsIndicator");
        postsIndicator->setGeometry(QRect(300, 50, 141, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginLabel->setText(QCoreApplication::translate("MainWindow", "Enter your username:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        profileLabel->setText(QCoreApplication::translate("MainWindow", "Your Profile:", nullptr));
        returnButton->setText(QCoreApplication::translate("MainWindow", "Return to your profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("MainWindow", "Add friend", nullptr));
        postsLabel->setText(QCoreApplication::translate("MainWindow", "Posts", nullptr));
        postsIndicator->setText(QCoreApplication::translate("MainWindow", "Recent Posts:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
