#ifndef CRASTERDATASET_H
#define CRASTERDATASET_H

#include <QThread>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

enum RasterDataType{VAR,CONST};
enum RasterType{TNOTYPE,TDEM,TSLOPE,TASPECT,TFUEL,TWINDSPEED,TWINDDIRECT,T1HMOISTURE,T10HMOISTURE,T100HMOISTURE,THERB,TWOOD};
class CRasterDataset : public QObject
{
    Q_OBJECT
private:
    int nCols; // number of columns
    int nRows; // number of rows
    double xLLCorner; // leftmost corner x coordinate
    double yLLCorner; // leftmost corner y coordinate
    float cellSize; // cell size
    float noDataValue; // no data value

    double * p; // pointer for data
    string strFile; // file name
    bool bDataReady; // whether the data is ready
    RasterDataType m_dataType;
    RasterType m_rasterType;
    double m_value;
public:

    CRasterDataset(string strFile);
    CRasterDataset();
    CRasterDataset(double value, int cols, int rows, double xll, double yll,float size, float nodata);
    ~CRasterDataset();

    friend std::ostream& operator<<(std::ostream& os, const CRasterDataset& r);
    friend std::istream& operator>>(std::istream&is, CRasterDataset& r);

    double operator[](const long& n);
    void setValue(const long& n, double value);

    string getStrFile() const;
    void setStrFile(const string &value);

    int readRasterData();
    bool isFileExist(const char* fileName);
    void allocateSpace();

    int getNCols() const;
    void setNCols(int value);

    int getNRows() const;
    void setNRows(int value);

    double getXLLCorner() const;
    void setXLLCorner(double value);

    double getYLLCorner() const;
    void setYLLCorner(double value);

    float getCellSize() const;
    void setCellSize(float value);

    float getNoDataValue() const;
    void setNoDataValue(float value);

    void readData();

    RasterType rasterType() const;
    void setRasterType(const RasterType &rasterType);

public slots:
    void finishReadData();
signals:
    void finished();
public slots:

};

#endif // CRASTERDATASET_H
