#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "dialogdata.h"
#include <QPictureIO>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include "cutilities.h"
#include <exception>
#include <QtCore>
#include <QThread>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bDataLoaded = false;
    pRaster = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isDataLoaded()
{
    return false;
}

void MainWindow::test()
{
    cout<<"test"<<endl;
    cout<<"data loaded"<<endl;
}


void MainWindow::on_actionImport_Data_triggered()
{
//    QString filters("Music files (*.mp3);;Text files (*.txt);;All files (*.*)");
//    QString defaultFilter("Text files (*.txt)");
//    QFileDialog fileDialog(0, "Select file", QDir::currentPath(), filters);
//    fileDialog.selectNameFilter(defaultFilter);
//    fileDialog.exec();
    QProgressDialog proDlg;

    int val = mTriggers.importDatasets(mProj);

    progressDlg.setRange(0,val);
    progressDlg.setValue(0);
    progressDlg.setWindowModality(Qt::WindowModal);
    progressDlg.show();

    QThread* thread = new QThread;
    mTriggers.moveToThread(thread);
    connect(thread,SIGNAL(started()),&mTriggers,SLOT(loadData()));
    connect(&mTriggers,SIGNAL(updateProgress()),this,SLOT(updateProgressValue()));
    thread->start(QThread::TimeCriticalPriority);

//    if(!mRaster.isDataLoaded() && mProj.getBIsProjLoaded())
//    {
//        pRaster = new CRasterDataset(mProj.getMFileDEM());
//        //pRaster->start(QThread::TimeCriticalPriority);
//        QThread* thread = new QThread;
//        pRaster->moveToThread(thread);

//        connect(thread, SIGNAL(started()), pRaster, SLOT(CRasterDataset::readData()));
//        connect(thread,SIGNAL(finished()),pRaster,SLOT(finishReadData()));
//        qDebug()<<"reading file is finished"<<"\n";
//        qDebug()<<"before started"<<"\n";
//        thread->start();
//    }
    //mRaster.loadRasterData(mProj);
}

void MainWindow::on_actionNew_Project_triggered()
{
    DialogData dlgData;
    if(dlgData.exec() == QDialog::Accepted)
    {
        cout<<"accept\n";
        mProj.setMFileDEM(dlgData.getMFileDEM());
        mProj.setMFileSlope(dlgData.getMFileSlope());
        mProj.setMFileAspect(dlgData.getMFileAspect());
        mProj.setMFileFuel(dlgData.getMFileFuel());
        mProj.setMWindSpeed(dlgData.getMWindSpeed());
        mProj.setMWindDirection(dlgData.getMWindDirection());
        mProj.setM1hMoisture(dlgData.getM1Moisture());
        mProj.setM10hMoisture(dlgData.getM10Moisture());
        mProj.setM100hMoisture(dlgData.getM100Moisture());
        mProj.setMherbMoisture(dlgData.getMHerbMoisture());
        mProj.setMwoodMoisture(dlgData.getMWoodMoisture());
        mProj.setBIsProjLoaded(true);
    }
// print the window
//    QPrinter prn;
//    prn.setPaperSize(QPrinter::A4);
//    prn.setResolution(100);
//    prn.setFullPage(true);
//    prn.setOrientation(QPrinter::Landscape);
//    prn.setOutputFormat(QPrinter::PdfFormat);
//    prn.setOutputFileName("out.pdf");
//    QPrintDialog(&prn, this).exec();
//    this->render(&prn);
}

void MainWindow::on_actionSave_Project_triggered()
{
    //save project file informaition
    const QString filters("Project files (*.wprj);;All files (*.*)");
    QString strFileName = QFileDialog::getSaveFileName(0,"Save projec file",QDir::currentPath(),filters,0,0);
    std::string strFile = strFileName.toLocal8Bit().constData();
    std::ofstream outf(strFile.c_str());
    mProj.setProjFileName(strFile);
    outf<<mProj;
    outf.close();

}
// calculate fire behavior
void MainWindow::on_actionFire_spread_modeling_triggered()
{
    mTriggers.calculateFireSpreadRates();
    mTriggers.createRasterNetwork();
//    if(mRaster.getNCellNum()>0){
//        mRaster.calculateFireBehavior();
//    }
//    else
//    {
//        QMessageBox::information(this,"No data","Data are not loaded");
//    }
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton msg;
    msg = QMessageBox::question(this,"Exit","Are you sure to quit the program?",QMessageBox::Yes|QMessageBox::No);
    if(msg == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void MainWindow::on_actionCalculate_trigger_buffers_triggered()
{
//    mRaster.createRasterNetwork();
//    mRaster.calculateTriggerBufer(50*100+50,120);
//    mRaster.writeTriggerBuffer("trigger.txt");
    mTriggers.calculateTriggerBuffer(50*100+50,120);
    qDebug()<<"calculate trigger buffer done\n";
    mTriggers.writeTriggerBuffer("trigger.txt");

    QImage image(mTriggers.getNCols(),mTriggers.getNRows(),QImage::Format_Mono);
    bool* pTB = mTriggers.getPTriggerBuffer();
    for(int i=0;i<mTriggers.getNRows();i++)
    {
        for(int j=0;j<mTriggers.getNCols();j++)
        {
            if(pTB[i*mTriggers.getNCols()+j])
            {
                image.setPixel(j,i,0);
            }
            else
            {
                image.setPixel(j,i,1);
            }
        }
    }
    if(image.isNull())
    {
        QMessageBox::information(this,"Image Viewer","Error Displaying image");
        return;
    }
    QGraphicsScene* scene = new QGraphicsScene();;
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::on_action_Open_triggered()
{
    //open a project file and load relevant information
    const QString filters("Project files (*.wprj);;All files (*.*)");
    QString strFileName = QFileDialog::getOpenFileName(0,"Open projec file",QDir::currentPath(),filters,0,0);
    std::string strFile = strFileName.toLocal8Bit().constData();
    std::ifstream inf(strFile.c_str());
    inf>>mProj;
    inf.close();
    mProj.setBIsProjLoaded(true);
    ui->statusBar->showMessage(strFileName);
}

void MainWindow::on_actionEdit_Project_File_triggered()
{
    DialogData dlgData;
    dlgData.setDialogData(mProj);

    if(dlgData.exec() == QDialog::Accepted)
    {
        cout<<"accept\n";
        mProj.setMFileDEM(dlgData.getMFileDEM());
        mProj.setMFileSlope(dlgData.getMFileSlope());
        mProj.setMFileAspect(dlgData.getMFileAspect());
        mProj.setMFileFuel(dlgData.getMFileFuel());
        mProj.setMWindSpeed(dlgData.getMWindSpeed());
        mProj.setMWindDirection(dlgData.getMWindDirection());
        mProj.setM1hMoisture(dlgData.getM1Moisture());
        mProj.setM10hMoisture(dlgData.getM10Moisture());
        mProj.setM100hMoisture(dlgData.getM100Moisture());
        mProj.setMherbMoisture(dlgData.getMHerbMoisture());
        mProj.setMwoodMoisture(dlgData.getMWoodMoisture());
        mProj.setBIsProjLoaded(true);
    }

}

void MainWindow::on_actionSet_model_input_triggered()
{

}

void MainWindow::on_actionExport_trigger_buffer_triggered()
{
//    QImage image(100,100,QImage::Format_Mono);
//    image.fill(1);
//    image.setPixel(50,0,0);
//    image.setPixel(50,1,0);
//    image.setPixel(51,1,0);
//    image.setPixel(49,1,0);

//    if(image.isNull())
//    {
//        QMessageBox::information(this,"Image Viewer","Error Displaying image");
//        return;
//    }
//    QGraphicsScene* scene = new QGraphicsScene();;
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
//    scene->addItem(item);

//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->show();
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->graphicsView->scale(1.2,1.2);
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->graphicsView->scale(0.8,0.8);
}

void MainWindow::on_actionPan_triggered()
{
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::updateProgressValue()
{
    progressDlg.setValue(progressDlg.value()+1);

}
