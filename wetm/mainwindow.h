#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cprojectfile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rasternet.h"
#include "crasterdataset.h"
#include "ctriggers.h"
#include <QProgressDialog>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isDataLoaded();
    void test();
    void importDatasets();
private slots:
    void on_actionImport_Data_triggered();

    void on_actionNew_Project_triggered();

    void on_actionSave_Project_triggered();

    void on_actionFire_spread_modeling_triggered();

    void on_actionExit_triggered();

    void on_actionCalculate_trigger_buffers_triggered();

    void on_action_Open_triggered();

    void on_actionEdit_Project_File_triggered();

    void on_actionSet_model_input_triggered();

    void on_actionExport_trigger_buffer_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionPan_triggered();

private slots:
    void updateProgressValue();
private:
    Ui::MainWindow *ui;

    CProjectFile mProj;
    CTriggers mTriggers;

    bool bDataLoaded;

    CRasterDataset* pRaster;

    QProgressDialog progressDlg;
    //ASCFileHeader * pHeader; // ASC file header
};

#endif // MAINWINDOW_H
