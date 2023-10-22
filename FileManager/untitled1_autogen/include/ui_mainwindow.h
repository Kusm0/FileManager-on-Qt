/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTreeView *treeView;
    QListView *listView;
    QPushButton *copyButton;
    QPushButton *deleteButton;
    QPushButton *renameButton;
    QPushButton *selectDirButton;
    QPushButton *pasteButton;
    QPushButton *privDirButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(10, 40, 321, 481));
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(340, 40, 301, 481));
        copyButton = new QPushButton(centralwidget);
        copyButton->setObjectName("copyButton");
        copyButton->setGeometry(QRect(660, 20, 80, 24));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(660, 140, 80, 24));
        renameButton = new QPushButton(centralwidget);
        renameButton->setObjectName("renameButton");
        renameButton->setGeometry(QRect(660, 80, 80, 24));
        selectDirButton = new QPushButton(centralwidget);
        selectDirButton->setObjectName("selectDirButton");
        selectDirButton->setGeometry(QRect(660, 110, 80, 24));
        pasteButton = new QPushButton(centralwidget);
        pasteButton->setObjectName("pasteButton");
        pasteButton->setGeometry(QRect(660, 50, 80, 24));
        privDirButton = new QPushButton(centralwidget);
        privDirButton->setObjectName("privDirButton");
        privDirButton->setGeometry(QRect(20, 10, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FileManager", nullptr));
        copyButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        renameButton->setText(QCoreApplication::translate("MainWindow", "Rename", nullptr));
        selectDirButton->setText(QCoreApplication::translate("MainWindow", "Dir", nullptr));
        pasteButton->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        privDirButton->setText(QCoreApplication::translate("MainWindow", "Previous Dir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
