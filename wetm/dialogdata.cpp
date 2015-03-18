#include "dialogdata.h"
#include "ui_dialogdata.h"
#include <QFileDialog>
//#include <QPrintDialog>
//#include <QPrinter>
#include "cutilities.h"

DialogData::DialogData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogData)
{
    ui->setupUi(this);

}

DialogData::~DialogData()
{
    delete ui;
}
// set up the values for the dialog before it is displayed
void DialogData::setDialogData(const CProjectFile& prj)
{
    ui->lineEdit_DEM->setText(CUtilities::StringToQstring(prj.getMFileDEM()));
    ui->lineEdit_slope->setText(CUtilities::StringToQstring(prj.getMFileSlope()));
    ui->lineEdit_aspect->setText(CUtilities::StringToQstring(prj.getMFileAspect()));
    ui->lineEdit_fuel->setText(CUtilities::StringToQstring(prj.getMFileFuel()));
    ui->doubleSpinBox_windspeed->setValue(prj.getMWindSpeed());
    ui->doubleSpinBox_windDirect->setValue(prj.getMWindDirection());
    ui->spinBox_1hM->setValue(prj.getM1hMoisture());
    ui->spinBox_10hM->setValue(prj.getM10hMoisture());
    ui->spinBox_100hM->setValue(prj.getM100hMoisture());
    ui->spinBox_herb->setValue(prj.getMherbMoisture());
    ui->spinBox_wood->setValue(prj.getMwoodMoisture());
}


void DialogData::on_buttonBox_accepted()
{
    mFileDEM  = QStringToString(ui->lineEdit_DEM->text());
    mFileSlope = QStringToString(ui->lineEdit_slope->text());
    mFileAspect = QStringToString(ui->lineEdit_aspect->text());
    mFileFuel = QStringToString(ui->lineEdit_fuel->text());

    mWindSpeed = ui->doubleSpinBox_windspeed->value();
    mWindDirection = ui->doubleSpinBox_windDirect->value();

    m1Moisture = ui->spinBox_1hM->value();
    m10Moisture = ui->spinBox_10hM->value();
    m100Moisture = ui->spinBox_100hM->value();
    mHerbMoisture = ui->spinBox_herb->value();
    mWoodMoisture = ui->spinBox_wood->value();

}

void DialogData::on_buttonBox_rejected()
{

}

void DialogData::on_toolBtn_DEM_clicked()
{
    const QString filters("DEM files (*.asc);;All files (*.*)");
    QString strFileName = QFileDialog::getOpenFileName(0,"Open DEM file",QDir::currentPath(),filters,0,0);
    ui->lineEdit_DEM->setText(strFileName);
}

void DialogData::on_toolBtn_slope_clicked()
{
    const QString filters("slope files (*.asc);;All files (*.*)");
    QString strFileName = QFileDialog::getOpenFileName(0,"Open slope file",QDir::currentPath(),filters,0,0);
    ui->lineEdit_slope->setText(strFileName);

}

void DialogData::on_toolBtn_aspect_clicked()
{
    const QString filters("aspect files (*.asc);;All files (*.*)");
    QString strFileName = QFileDialog::getOpenFileName(0,"Open aspect file",QDir::currentPath(),filters,0,0);
    ui->lineEdit_aspect->setText(strFileName);
}

void DialogData::on_toolBtn_fuel_clicked()
{
    const QString filters("fuel files (*.asc);;All files (*.*)");
    QString strFileName = QFileDialog::getOpenFileName(0,"Open fuel file",QDir::currentPath(),filters,0,0);
    ui->lineEdit_fuel->setText(strFileName);

}
double DialogData::getMWoodMoisture() const
{
    return mWoodMoisture;
}

void DialogData::setMWoodMoisture(double value)
{
    mWoodMoisture = value;
}

string DialogData::QStringToString(const QString &str)
{
    std::string strCPP = str.toLocal8Bit().constData();
    return strCPP;
}

double DialogData::getMHerbMoisture() const
{
    return mHerbMoisture;
}

void DialogData::setMHerbMoisture(double value)
{
    mHerbMoisture = value;
}

double DialogData::getM100Moisture() const
{
    return m100Moisture;
}

void DialogData::setM100Moisture(double value)
{
    m100Moisture = value;
}

double DialogData::getM10Moisture() const
{
    return m10Moisture;
}

void DialogData::setM10Moisture(double value)
{
    m10Moisture = value;
}

double DialogData::getM1Moisture() const
{
    return m1Moisture;
}

void DialogData::setM1Moisture(double value)
{
    m1Moisture = value;
}

double DialogData::getMWindDirection() const
{
    return mWindDirection;
}

void DialogData::setMWindDirection(double value)
{
    mWindDirection = value;
}

double DialogData::getMWindSpeed() const
{
    return mWindSpeed;
}

void DialogData::setMWindSpeed(double value)
{
    mWindSpeed = value;
}

string DialogData::getMFileFuel() const
{
    return mFileFuel;
}

void DialogData::setMFileFuel(const string &value)
{
    mFileFuel = value;
}

string DialogData::getMFileAspect() const
{
    return mFileAspect;
}

void DialogData::setMFileAspect(const string &value)
{
    mFileAspect = value;
}

string DialogData::getMFileSlope() const
{
    return mFileSlope;
}

void DialogData::setMFileSlope(const string &value)
{
    mFileSlope = value;
}

string DialogData::getMFileDEM() const
{
    return mFileDEM;
}

void DialogData::setMFileDEM(const string &value)
{
    mFileDEM = value;
}

