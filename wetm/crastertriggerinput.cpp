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
    try
    {
        vector<long> cellArray;
        cout<<nRows<<" "<<nCols<<endl;
        if(p!=NULL)
        {
            for (long i=0;i<nRows*nCols;i++)
            {
                if(p[i] == 1.0)
                {
                    cellArray.push_back(i);
                }
            }
        }
        cout<<"cellArray vector size: "<<cellArray.size()<<endl;
        //calculate all the boundary cells and store their IDs in a new array
        vector<long> boundaryCellArray;

        if ( nRows>0 && nCols>0)
        {
            long nCellNum = nRows*nCols;
            //create an array to store the input cells
            bool * pCellData = new bool[nCellNum];
            for (int i=0;i<nRows;i++)
            {
                for (int j=0;j<nCols;j++)
                {
                    int n = j + i*nCols;
                    pCellData[n] = false; //initialize the cells to unselected
                }
            }

            //set all the input cells to true
            for (vector<long>::iterator it = cellArray.begin();it!=cellArray.end();++it)
            {
                //cout<<"value: "<<*it<<endl;
                pCellData[*it]= true;
            }
            //extract the boundary cells
            for (vector<long>::iterator it = cellArray.begin();it!=cellArray.end();++it)
            {
                //first judge whether the cells are on the boundary of the raster data
                if (*it/nCols==0 || *it/nCols==nRows-1 || *it%nCols==0 ||*it%nCols==nCols-1)
                {
                    boundaryCellArray.push_back(*it);
                }
                else //judge the eight neighbor cells for each cell in cellArray
                {
                    if(!(pCellData[*it-nCols] && pCellData[*it-nCols-1] && pCellData[*it-nCols+1] && pCellData[*it-1]
                    && pCellData[*it+1] && pCellData[*it+nCols] && pCellData[*it+nCols-1] && pCellData[*it +nCols+1]))
                    {
                        boundaryCellArray.push_back(*it);
                        //cout<<"boundary cell ID: "<<*it<<endl;
                    }

                }

            }//end for

            //delete the cell array
            if (pCellData!=NULL)
            {
                delete [] pCellData;
            }
        }//end if

        cout<<"total number of boundary cells in the cell file: "<<boundaryCellArray.size()<<endl;
        for(vector<long>::iterator it = boundaryCellArray.begin(); it != boundaryCellArray.end();it++)
        {
            cout<<*it<<endl;
        }
        return boundaryCellArray; // return the final array
    } //end try
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }


}


