#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <omp.h>
#include "cprojectfile.h"
#include "fireLib.h"
using namespace std;

#define MAXCOST 99999.0

class ASCFileHeader
{
private:
	int nCols; // number of columns
	int nRows; // number of rows
	double xLLCorner; // leftmost corner x coordinate
	double yLLCorner; // leftmost corner y coordinate
	float cellSize;
	float noDataValue;
public:
	//ASCFileHeader()
	//{
	//	nCols = 0;
	//	nRows = 0;
	//	xLLCorner = 0.0;
	//	yLLCorner = 0.0;
	//	cellSize = 0.0;
	//	noDataValue = -99999.0;
	//}
	ASCFileHeader(int cols = 0, int rows = 0,double xLL=0.0, double yLL = 0.0, float resolution = 0.0, float noData = -9999.0)
	{
		nCols = cols;
		nRows = rows;
		xLLCorner = xLL;
		yLLCorner = yLL;
		cellSize = resolution;
		noDataValue = noData;
	}
    ASCFileHeader(const ASCFileHeader& fh ){
        nCols = fh.nCols;
        nRows = fh.nRows;
        xLLCorner = fh.xLLCorner;
        yLLCorner = fh.yLLCorner;
        cellSize = fh.cellSize;
        noDataValue = fh.noDataValue;
    }

	~ASCFileHeader()
	{

	}
	int getCols(){return nCols;}
	int setCols(int cols=0) {return nCols = cols;}

	int getRows(){return nRows;}
	int setRows(int rows = 0) {return nRows = rows;}

	double getXLLCorner(){return xLLCorner;}
	double setXLLCorner(double xLL = 0.0){return xLLCorner = xLL;}

	double getYLLCorner(){return yLLCorner;}
	double setYLLCorner(double yLL = 0.0){return yLLCorner = yLL;}

	float getCellSize(){return cellSize;}
	float setCellSize(float resolution){return cellSize = resolution;}

	float getNoDataValue(){return noDataValue;}
	float setNoDataValue(float noData = 0.0){return noDataValue = noData;}
};

class CRasterNet
{
	
public:
	CRasterNet(void);
	~CRasterNet(void);
	int readROSRasterData(string strFileName,float** ptr[]);
	int readROSRasterData(string strFileName,float* ptr[]);
	int readROSRasterData(string strFileName);
	int createRasterNetwork();
	int Dijkstra(int source, int time);
	int getNeighborID(int node,int direction);
	float arcCost(int node1,int node2);
	int writeTriggerBuffer(string strFileName);
	int readCellFile(string strCellFile);
	int calculateTriggerBufer(int cellID,int time);
    void deleteRasterData();
    void loadRasterData(const CProjectFile& prj);
    int readRasterData(string strFileName, double*& ptr);
    int readRasterData(string strFileName, int *&ptr);
    int createRasterData(double value, double*& ptr);
    void calculateFireBehavior();
    void adjustWindSpeed();
    void adjustWindSpeedN();
    bool isDataLoaded();

    int getNRows() const;
    void setNRows(int value);

    int getNCols() const;
    void setNCols(int value);

    bool *getPTriggerBuffer() const;
    void setPTriggerBuffer(bool *value);

    int getNCellNum() const;
    void setNCellNum(int value);

private:
    ASCFileHeader * pHeader; // ASC file header
    float * pROSData[8]; //Rate of spread data
	int nRows, nCols; //the number of rows and columns
	int nCellNum; // the total number of raster cells
	float cellRes; // the resolution of raster cells (in meters)
	vector<int> cellArray; //the input cells for WUIVAC
	vector<int> boundaryCellArray; //the input boundary cells for WUIVAC
	//bool * pSelectedList;
	float ** pArcList; // the arc data (arc cost)
	bool * pTriggerBuffer; //the final trigger buffer
	//float * pMinCostList;
    double* pDEM;
    double* pSlope;
    double* pAspect;
    int* pFuel;
    double* pWindSpeed;
    double* pWindDirect;
    double* p1hMoisture;
    double* p10hMoisture;
    double* p100hMoisture;
    double* pHerbMoisture;
    double* pWoodMoisture;
};
