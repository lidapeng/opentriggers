#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>
#include <string>
#include <iostream>
#include "cprojectfile.h"
using namespace std;

namespace Ui {
class DialogData;
}

class DialogData : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogData(QWidget *parent = 0);
    ~DialogData();

    void setDialogData(const CProjectFile& prj);

    string getMFileDEM() const;
    void setMFileDEM(const string &value);

    string getMFileSlope() const;
    void setMFileSlope(const string &value);

    string getMFileAspect() const;
    void setMFileAspect(const string &value);

    string getMFileFuel() const;
    void setMFileFuel(const string &value);

    double getMWindSpeed() const;
    void setMWindSpeed(double value);

    double getMWindDirection() const;
    void setMWindDirection(double value);

    double getM1Moisture() const;
    void setM1Moisture(double value);

    double getM10Moisture() const;
    void setM10Moisture(double value);

    double getM100Moisture() const;
    void setM100Moisture(double value);

    double getMHerbMoisture() const;
    void setMHerbMoisture(double value);

    double getMWoodMoisture() const;
    void setMWoodMoisture(double value);
    std::string QStringToString(const QString& str);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_toolBtn_DEM_clicked();

    void on_toolBtn_slope_clicked();

    void on_toolBtn_aspect_clicked();

    void on_toolBtn_fuel_clicked();

private:
    Ui::DialogData *ui;
    string mFileDEM;
    string mFileSlope;
    string mFileAspect;
    string mFileFuel;
    double mWindSpeed; //mph
    double mWindDirection; //degrees from north
    double m1Moisture; // 1 hour moisture
    double m10Moisture; // 10 hour moisture
    double m100Moisture; // 100 hour moisture
    double mHerbMoisture; // herb moisture
    double mWoodMoisture; // wood moisture
};

#endif // DIALOGDATA_H
