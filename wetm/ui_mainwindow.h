/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *actionImport_Data;
    QAction *actionNew_Project;
    QAction *actionSave_Project;
    QAction *actionFire_spread_modeling;
    QAction *actionExit;
    QAction *actionCalculate_trigger_buffers;
    QAction *actionEdit_Project_File;
    QAction *actionSet_model_input;
    QAction *actionPan;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionExport_trigger_buffer;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuData;
    QMenu *menuTriggers;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(564, 316);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/openfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon);
        actionImport_Data = new QAction(MainWindow);
        actionImport_Data->setObjectName(QString::fromUtf8("actionImport_Data"));
        actionImport_Data->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/importdata.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport_Data->setIcon(icon1);
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/newfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Project->setIcon(icon2);
        actionSave_Project = new QAction(MainWindow);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/savefile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project->setIcon(icon3);
        actionFire_spread_modeling = new QAction(MainWindow);
        actionFire_spread_modeling->setObjectName(QString::fromUtf8("actionFire_spread_modeling"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/fire.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actionFire_spread_modeling->setIcon(icon4);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionCalculate_trigger_buffers = new QAction(MainWindow);
        actionCalculate_trigger_buffers->setObjectName(QString::fromUtf8("actionCalculate_trigger_buffers"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/buffer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalculate_trigger_buffers->setIcon(icon5);
        actionEdit_Project_File = new QAction(MainWindow);
        actionEdit_Project_File->setObjectName(QString::fromUtf8("actionEdit_Project_File"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/projects.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit_Project_File->setIcon(icon6);
        actionSet_model_input = new QAction(MainWindow);
        actionSet_model_input->setObjectName(QString::fromUtf8("actionSet_model_input"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/icons/point1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_model_input->setIcon(icon7);
        actionPan = new QAction(MainWindow);
        actionPan->setObjectName(QString::fromUtf8("actionPan"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/icons/draghand.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPan->setIcon(icon8);
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/icons/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon9);
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/icons/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon10);
        actionExport_trigger_buffer = new QAction(MainWindow);
        actionExport_trigger_buffer->setObjectName(QString::fromUtf8("actionExport_trigger_buffer"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/icons/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport_trigger_buffer->setIcon(icon11);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 564, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuData = new QMenu(menuBar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        menuTriggers = new QMenu(menuBar);
        menuTriggers->setObjectName(QString::fromUtf8("menuTriggers"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuData->menuAction());
        menuBar->addAction(menuTriggers->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(action_Open);
        menuFile->addAction(actionSave_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionExport_trigger_buffer);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuData->addAction(actionEdit_Project_File);
        menuData->addAction(actionImport_Data);
        menuTriggers->addAction(actionFire_spread_modeling);
        menuTriggers->addAction(actionSet_model_input);
        menuTriggers->addAction(actionCalculate_trigger_buffers);
        menuView->addAction(actionPan);
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        mainToolBar->addAction(actionNew_Project);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(actionEdit_Project_File);
        mainToolBar->addAction(actionImport_Data);
        mainToolBar->addAction(actionExport_trigger_buffer);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPan);
        mainToolBar->addAction(actionZoom_in);
        mainToolBar->addAction(actionZoom_out);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionFire_spread_modeling);
        mainToolBar->addAction(actionSet_model_input);
        mainToolBar->addAction(actionCalculate_trigger_buffers);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Triggers", 0));
        action_Open->setText(QApplication::translate("MainWindow", "Open Project", 0));
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionImport_Data->setText(QApplication::translate("MainWindow", "&Import Data", 0));
        actionImport_Data->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", 0));
        actionNew_Project->setText(QApplication::translate("MainWindow", "New Project", 0 ));
        actionNew_Project->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0  ));
        actionSave_Project->setText(QApplication::translate("MainWindow", "Save Project", 0  ));
        actionSave_Project->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0  ));
        actionFire_spread_modeling->setText(QApplication::translate("MainWindow", "Fire spread modeling", 0  ));
        actionFire_spread_modeling->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0  ));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0  ));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0  ));
        actionCalculate_trigger_buffers->setText(QApplication::translate("MainWindow", "Calculate trigger buffers", 0  ));
        actionEdit_Project_File->setText(QApplication::translate("MainWindow", "Edit Project File", 0  ));
        actionEdit_Project_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0  ));
        actionSet_model_input->setText(QApplication::translate("MainWindow", "Set model input", 0  ));
        actionPan->setText(QApplication::translate("MainWindow", "Pan", 0  ));
        actionZoom_in->setText(QApplication::translate("MainWindow", "Zoom in", 0  ));
        actionZoom_out->setText(QApplication::translate("MainWindow", "Zoom out", 0  ));
        actionExport_trigger_buffer->setText(QApplication::translate("MainWindow", "Export trigger buffer", 0  ));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0  ));
        menuData->setTitle(QApplication::translate("MainWindow", "Data", 0  ));
        menuTriggers->setTitle(QApplication::translate("MainWindow", "Triggers", 0  ));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0  ));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
