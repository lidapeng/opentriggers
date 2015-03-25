#include "crastertriggerinput.h"

CRasterTriggerInput::CRasterTriggerInput()
{
}

CRasterTriggerInput::CRasterTriggerInput(string strFile)
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

}

vector<long> CRasterTriggerInput::getInputRasterFeature()
{
    vector<long> vInput;
    cout<<nRows<<" "<<nCols<<endl;
    if(p!=NULL)
    {
        for (long i=0;i<nRows*nCols;i++)
        {
            if(p[i] == 1.0)
            {
                vInput.push_back(i);
            }
        }
    }
    cout<<"vector size: "<<vInput.size()<<endl;
    return vInput;
}


