#include "crasterdataset.h"
#include <QProgressDialog>
#include <QtCore>
string CRasterDataset::getStrFile() const
{
    return strFile;
}

void CRasterDataset::setStrFile(const string &value)
{
    strFile = value;
}

int CRasterDataset::readRasterData()
{
    if (isFileExist(strFile.c_str()))
    {
        try
        {
            FILE *fpin;
            cout<<"\nReading input data: "<<strFile<<endl;
            char temp[20];
            if ((fpin = fopen(strFile.c_str(), "r")) != NULL)
            {
                fscanf(fpin, "%s %d\n", temp, &nCols);
                fscanf(fpin, "%s %d\n", temp, &nRows);
                fscanf(fpin, "%s %lf\n", temp, &xLLCorner);
                fscanf(fpin, "%s %lf\n", temp, &yLLCorner);
                fscanf(fpin, "%s %f\n", temp, &cellSize);
                fscanf(fpin, "%s %f\n", temp, &noDataValue);
                //cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;
                if(nRows>0 && nCols>0)
                {
                    p = new double[nRows*nCols];
                    for(int i = 0;i<nRows*nCols;i++)
                    {
                        fscanf(fpin,"%lf",&p[i]);
                    }
                }

            }
            fclose(fpin);
            return 0;

        }
        catch (exception& e)
        {
            std::cout<<e.what()<<endl;
        }

    }
    else
    {
        bDataReady = false;
        return -1;
    }
    return 0;
}

bool CRasterDataset::isFileExist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void CRasterDataset::readData()
{
    // if data needs to be read from a file
    if (m_dataType == VAR)
    {
        if(isFileExist(strFile.c_str()))
        {
            ifstream ifs (strFile.c_str());
            ifs>>*this;
            ifs.close();
            qDebug()<<"reading file finished\n";
        }
    }
    //otherwise create a dataset
    else
    {
        if(p == NULL)
        {
            p = new double[nRows*nCols];
            // if the dataset is a moisture dataset
//            if(m_rasterType == T1HMOISTURE||m_rasterType==T10HMOISTURE||m_rasterType==T100HMOISTURE||m_rasterType==TWOOD||m_rasterType==THERB)
//            {
            for(long i=0;i<nRows*nCols; i++)
            {
                p[i] = m_value;
            }
//            }
            qDebug()<<"creating data finished\n";
        }
    }

}

void CRasterDataset::finishReadData()
{
    qDebug()<<"Reading data finished"<<"\n";
}

int CRasterDataset::getNCols() const
{
    return nCols;
}

void CRasterDataset::setNCols(int value)
{
    nCols = value;
}

int CRasterDataset::getNRows() const
{
    return nRows;
}

void CRasterDataset::setNRows(int value)
{
    nRows = value;
}

double CRasterDataset::getXLLCorner() const
{
    return xLLCorner;
}

void CRasterDataset::setXLLCorner(double value)
{
    xLLCorner = value;
}

double CRasterDataset::getYLLCorner() const
{
    return yLLCorner;
}

void CRasterDataset::setYLLCorner(double value)
{
    yLLCorner = value;
}

float CRasterDataset::getCellSize() const
{
    return cellSize;
}

void CRasterDataset::setCellSize(float value)
{
    cellSize = value;
}

float CRasterDataset::getNoDataValue() const
{
    return noDataValue;
}

void CRasterDataset::setNoDataValue(float value)
{
    noDataValue = value;
}

RasterType CRasterDataset::rasterType() const
{
    return m_rasterType;
}

void CRasterDataset::setRasterType(const RasterType &rasterType)
{
    m_rasterType = rasterType;
}
CRasterDataset::CRasterDataset(string strFile)
{
    p = NULL;
    bDataReady = false;
    this->strFile = strFile;
    m_dataType = VAR;
    m_value = -1;
    nRows = 0;
    nCols =0;
    xLLCorner = 0.0;
    yLLCorner = 0.0;
    cellSize = 0.0;
    noDataValue = -9999.0;
    m_rasterType = TNOTYPE;
    qDebug()<<m_dataType<<" "<<VAR<<"\n";
}

CRasterDataset::CRasterDataset()
{
    p = NULL;
    bDataReady = false;
    this->strFile = "";
    m_dataType = VAR;
    nCols = 0;
    nRows = 0;
    xLLCorner = 0.0;
    yLLCorner = 0.0;
    cellSize = 0.0;
    noDataValue = -9999.0;
    m_rasterType = TNOTYPE;
}

CRasterDataset::CRasterDataset(double value, int cols, int rows, double xll, double yll,float size, float nodata)
{
    p = NULL;
    bDataReady = false;
    this->strFile = strFile;
    m_dataType = CONST;
    m_value = value;
    if(cols>0)
    {
        nCols = cols;
    }
    else
        nCols = 0;
    if(rows>0)
        nRows = rows;
    else
        nRows = 0;
    xLLCorner = xll;
    yLLCorner = yll;
    cellSize = size;
    noDataValue = nodata;
}

CRasterDataset::~CRasterDataset()
{
    if(p!=NULL)
    {
        delete [] p;
    }
}

double CRasterDataset::operator[](const long &n)
{
    try
    {
        if (n < nRows*nCols && p !=NULL)
        {
            return p[n];
        }
        else
        {
            cout<<"invalid value"<<endl;
        }
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }
    double rval = (double)noDataValue;
    return rval;

}

void CRasterDataset::setValue(const long &n, double value)
{
    try
    {
        if(n<nRows*nCols && n>=0 && p!=NULL && value>=0)
        {
            p[n] = value;
        }
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }

}

ostream & operator<<(ostream& os, const CRasterDataset &r)
{
    os<< "ncols"<<'\t'<< r.nCols<<'\n';
    os<<"nrows"<<'\t'<<r.nRows<<'\n';
    os<<"xllcorner"<<'\t'<<r.xLLCorner<<'\n';
    os<<"yllcorner"<<'\t'<<r.yLLCorner<<'\n';
    os<<"cellsize"<<'\t'<<r.cellSize<<'\n';
    os<<"NODATA_value"<<'\t'<<r.noDataValue<<'\n';
    if(r.p!=NULL && r.nCols>0 && r.nRows>0)
    {
        for(long i =0;i<r.nCols*r.nRows;i++)
        {
            os<<r.p[i];
        }
    }
    return os;
}
istream & operator>>(istream& is, CRasterDataset& r)
{
    string temp;

    is>>temp>>r.nCols;
    is>>temp>>r.nRows;
    is>>temp>>r.xLLCorner;
    is>>temp>>r.yLLCorner;
    is>>temp>>r.cellSize;
    is>>temp>>r.noDataValue;
//    QProgressDialog progress("Copying files...", "Abort Copy", 0, r.nCols*r.nRows);
//    progress.setWindowModality(Qt::WindowModal);
    try
    {
        if(r.nCols>0 && r.nRows>0)
        {
            if(r.p!=NULL)
            {
                delete [] r.p;
            }
            r.p = new double[r.nCols*r.nRows];

            for(long i=0;i<r.nCols*r.nRows;i++)
            {
                is>>r.p[i];
//                progress.setValue(i);
            }
        }
//        progress.setValue(r.nCols*r.nRows);
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }


    return is;
}
