/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Addtask;
    QTableWidget *TaskTable;
    QGridLayout *gridLayout;
    QPushButton *DeleteTask;
    QPushButton *SaveTask;
    QPushButton *Renametask;
    QPushButton *LoadTask;
    QMenuBar *menubar;
    QMenu *menutime_tracker;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(100, 0, 311, 471));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Addtask = new QPushButton(layoutWidget);
        Addtask->setObjectName("Addtask");

        verticalLayout->addWidget(Addtask);

        TaskTable = new QTableWidget(layoutWidget);
        if (TaskTable->columnCount() < 3)
            TaskTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TaskTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TaskTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TaskTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        TaskTable->setObjectName("TaskTable");

        verticalLayout->addWidget(TaskTable);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        DeleteTask = new QPushButton(layoutWidget);
        DeleteTask->setObjectName("DeleteTask");

        gridLayout->addWidget(DeleteTask, 0, 0, 1, 1);

        SaveTask = new QPushButton(layoutWidget);
        SaveTask->setObjectName("SaveTask");

        gridLayout->addWidget(SaveTask, 1, 1, 1, 1);

        Renametask = new QPushButton(layoutWidget);
        Renametask->setObjectName("Renametask");

        gridLayout->addWidget(Renametask, 0, 1, 1, 1);

        LoadTask = new QPushButton(layoutWidget);
        LoadTask->setObjectName("LoadTask");

        gridLayout->addWidget(LoadTask, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menutime_tracker = new QMenu(menubar);
        menutime_tracker->setObjectName("menutime_tracker");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menutime_tracker->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Addtask->setText(QCoreApplication::translate("MainWindow", "ajouter une tache", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TaskTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Tache", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TaskTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Temps", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TaskTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Action", nullptr));
        DeleteTask->setText(QCoreApplication::translate("MainWindow", "spprimer une tache", nullptr));
        SaveTask->setText(QCoreApplication::translate("MainWindow", "Sauvegarder tache", nullptr));
        Renametask->setText(QCoreApplication::translate("MainWindow", "Rennomer une tache", nullptr));
        LoadTask->setText(QCoreApplication::translate("MainWindow", "ChargerTache", nullptr));
        menutime_tracker->setTitle(QCoreApplication::translate("MainWindow", "time tracker", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
