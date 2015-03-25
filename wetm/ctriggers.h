#ifndef CTRIGGERS_H
#define CTRIGGERS_H
#include "cprojectfile.h"
#include "crasterdataset.h"
#include <iostream>
#include <string>
#include <vector>
#include <QtCore>
#include "fireLib.h"
#include <set>
#include <cmath>
using namespace std;

// CTriggers class has the following functionalities:
// 1) calculate fire behaviors using fireLib;
// 2) calculate fire travel times between two raster cells and build the travel-time network
// 3) calculate the trigger buffer using the shortest path algorithm

class CTriggers :public QObject
{
    Q_OBJECT
    // data variables
//public:
//    static const double TMAXCOST;
private:
    double TMAXCOST;
private:
    vector<CRasterDataset*> vecRaster;

    // raster data information
    int nCols; // number of columns
    int nRows; // number of rows
    double xLLCorner; // leftmost corner x coordinate
    double yLLCorner; // leftmost corner y coordinate
    float cellSize; // cell size
    float noDataValue; // no data value

    // raster fire spread rates (8 directions)
    float* pROS[8];
    // the arc data (arc cost)
    float ** pArcList;
    //the final trigger buffer
    bool * pTriggerBuffer;

    vector<long> cellArray; //the input cells for WUIVAC
    vector<long> boundaryCellArray; //the input boundary cells for WUIVAC
public:
    CTriggers();
    ~CTriggers();
    void deleteRasterData();
    int importDatasets(const CProjectFile& prj);

    int createRasterData(const double& value, double *&ptr);
    void adjustWindSpeedN(); // adjust wind speed
    void getRasterHeader(const string &strFile);

    int calculateFireSpreadRates();
    int createRasterNetwork();
    int Dijkstra(long source, int time);
    long getNeighborID(long node, int direction); // get the neighor's ID
    float arcCost(long node1,long node2); // get arc cost

    int readInputCellFile(string strFileName); //old function
    int getBoundaryCells(string strFileName);

    int calculateTriggerBuffer(long cellID, int time);
    int writeTriggerBuffer(string strFileName);
    bool *getPTriggerBuffer() const;
    void setPTriggerBuffer(bool *value);

    int getNCols() const;
    void setNCols(int value);

    int getNRows() const;
    void setNRows(int value);

public slots:
    void loadData();
signals:
    void updateProgress();

};

#endif // CPROJECTDATA_H
