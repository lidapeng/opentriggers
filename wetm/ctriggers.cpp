#include "ctriggers.h"
#include "crastertriggerinput.h"
//constructor

bool *CTriggers::getPTriggerBuffer() const
{
    return pTriggerBuffer;
}

void CTriggers::setPTriggerBuffer(bool *value)
{
    pTriggerBuffer = value;
}

int CTriggers::getNCols() const
{
    return nCols;
}

void CTriggers::setNCols(int value)
{
    nCols = value;
}

int CTriggers::getNRows() const
{
    return nRows;
}

void CTriggers::setNRows(int value)
{
    nRows = value;
}
CTriggers::CTriggers()
{
    for(int i=0;i<8;i++)
    {
        pROS[i] = NULL;
    }
    //pHeader = NULL;
    TMAXCOST = 9999.0;
    pArcList = NULL; //initialize arc
    pTriggerBuffer = NULL;
}
//destructor
CTriggers::~CTriggers()
{
    //deleteRasterData();
    for(int i=0;i<vecRaster.size();i++)
    {
        delete vecRaster[i];
    }
    vecRaster.clear();
    for(int i=0;i<8;i++)
    {
        if (pROS[i]!=NULL)
        {
            delete [] pROS[i];
        }
    }
    if (pArcList!=NULL)
    {
        for(int i = 0; i<nRows*nCols;i++)
            delete [] pArcList[i];
        delete [] pArcList;
    }
    if(pTriggerBuffer !=NULL)
    {
        delete [] pTriggerBuffer;
    }
}

void CTriggers::deleteRasterData()
{

}

int CTriggers::importDatasets(const CProjectFile &prj)
{
    getRasterHeader(prj.getMFileDEM());

    CRasterDataset* pRFuel = new CRasterDataset(prj.getMFileFuel());
    CRasterDataset* pRDEM = new CRasterDataset(prj.getMFileDEM());
    CRasterDataset* pRAspect = new CRasterDataset(prj.getMFileAspect());
    CRasterDataset* pRSlope = new CRasterDataset(prj.getMFileSlope());
    CRasterDataset* pRWindSpeed = new CRasterDataset(prj.getMWindSpeed(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);
    CRasterDataset* pRWindDirection = new CRasterDataset(prj.getMWindDirection(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);

    CRasterDataset* pR1hMoisture = new CRasterDataset(prj.getM1hMoisture(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);
    CRasterDataset* pR10Moisture = new CRasterDataset(prj.getM10hMoisture(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);
    CRasterDataset* pR100hMoisture = new CRasterDataset(prj.getM100hMoisture(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);
    CRasterDataset* pRHerbMoisture = new CRasterDataset(prj.getMherbMoisture(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);
    CRasterDataset* pRWoodMoisture = new CRasterDataset(prj.getMwoodMoisture(),nCols,nRows,xLLCorner,yLLCorner,cellSize,noDataValue);

    pRFuel->setRasterType(TFUEL);
    pRDEM->setRasterType(TDEM);
    pRAspect->setRasterType(TASPECT);
    pRSlope->setRasterType(TSLOPE);
    pRWindSpeed->setRasterType(TWINDSPEED);
    pRWindDirection->setRasterType(TWINDDIRECT);
    pR1hMoisture->setRasterType(T1HMOISTURE);
    pR10Moisture->setRasterType(T10HMOISTURE);
    pR100hMoisture->setRasterType(T100HMOISTURE);
    pRHerbMoisture->setRasterType(THERB);
    pRWoodMoisture->setRasterType(TWOOD);

    vecRaster.push_back(pRFuel); //0
    vecRaster.push_back(pRDEM); //1
    vecRaster.push_back(pRAspect); //2
    vecRaster.push_back(pRSlope); //3
    vecRaster.push_back(pRWindSpeed); //4
    vecRaster.push_back(pRWindDirection);//5

    vecRaster.push_back(pR1hMoisture);//6
    vecRaster.push_back(pR10Moisture); //7
    vecRaster.push_back(pR100hMoisture);//8
    vecRaster.push_back(pRHerbMoisture);//9
    vecRaster.push_back(pRWoodMoisture);//10

    return vecRaster.size();
}

void CTriggers::loadData()
{
    for(int i=0;i<vecRaster.size();i++)
    {
        vecRaster[i]->readData();
        emit updateProgress();
    }
    adjustWindSpeedN();
}

void CTriggers::adjustWindSpeedN()
{
    if(vecRaster.size()>0)
    {
        try
        {
            if(vecRaster[0]->rasterType() == TFUEL && vecRaster[4]->rasterType() == TWINDSPEED)
            {
                long n = nRows*nCols;
                for(long i=0;i<n;i++)
                {
                    switch((int)(*vecRaster[0])[i])
                    {
                    case 1:
//                        cout<<(*vecRaster[4])[i]<<endl;
                    vecRaster[4]->setValue(i, 0.36*88.0*(*vecRaster[4])[i]);
//                    cout<<(*vecRaster[4])[i]<<endl;
                    break;
                    case 2:
                    vecRaster[4]->setValue(i, 0.36*88.0*(*vecRaster[4])[i]);
                    break;
                    case 3:
                    vecRaster[4]->setValue(i, 0.44*88.0*(*vecRaster[4])[i]);
                    break;
                    case 4:
                        vecRaster[4]->setValue(i, 0.55*88.0*(*vecRaster[4])[i]);
                        break;
                    case 5:
                    vecRaster[4]->setValue(i, 0.42*88.0*(*vecRaster[4])[i]);
                    break;
                    case 6:
                    vecRaster[4]->setValue(i, 0.44*88.0*(*vecRaster[4])[i]);
                    break;
                    case 7:
                    vecRaster[4]->setValue(i, 0.44*88.0*(*vecRaster[4])[i]);
                    break;
                    case 8:
                    vecRaster[4]->setValue(i, 0.28*88.0*(*vecRaster[4])[i]);
                    break;
                    case 9:
                    vecRaster[4]->setValue(i, 0.28*88.0*(*vecRaster[4])[i]);
                    break;
                    case 10:
                    vecRaster[4]->setValue(i, 0.36*88.0*(*vecRaster[4])[i]);
                    break;
                    case 11:
                    vecRaster[4]->setValue(i, 0.36*88.0*(*vecRaster[4])[i]);
                    break;
                    case 12:
                    vecRaster[4]->setValue(i, 0.43*88.0*(*vecRaster[4])[i]);
                    break;
                    case 13:
                    vecRaster[4]->setValue(i, 0.46*88.0*(*vecRaster[4])[i]);
                    break;
                    }

                }
            }
            qDebug()<<"Wind speed adjusted\n";
        }
        catch (exception&e)
        {
            cout<<e.what()<<endl;
        }
    }
}

void CTriggers::getRasterHeader(const string &strFile)
{
    try
    {

       string temp;
       ifstream ifs(strFile.c_str());
       ifs>>temp>>nCols;
       ifs>>temp>>nRows;
       ifs>>temp>>xLLCorner;
       ifs>>temp>>yLLCorner;
       ifs>>temp>>cellSize;
       ifs>>temp>>noDataValue;
       ifs.close();
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }

}

int CTriggers::calculateFireSpreadRates()
{
    try
    {
        /* NOTE 6: create a standard fuel model catalog and a flame length table. */
        FuelCatalogPtr catalog = Fire_FuelCatalogCreateStandard("Standard", 13);
        //add fuel models FM97,FM98,FM99
    //    Fire_FuelModelCreate(catalog,15,"FM15","nofuel",0.1,0.01,1.0,0);
    //    Fire_FuelModelCreate(catalog,28,"FM28","nofuel",0.1,0.01,1.0,0);

    //    Fire_FuelModelCreate(catalog,97,"FM97","nofuel",0.1,0.01,1.0,0);
    //    Fire_FuelModelCreate(catalog,98,"FM98","water",0.1,0.01,1.0,0);
    //    Fire_FuelModelCreate(catalog,99,"FM99","barren",0.1,0.01,1.0,0);

        Fire_FlameLengthTable(catalog, 500, 0.1);
        double nAzm[8];
        /* Calculate distance across cell to each neighbor and its azimuth. */
        for (int n=0; n<8; n++ )
        {
            nAzm[n] = n * 45.;
        }
        long N = nRows*nCols;
        cout<<N<<endl;
        double moisture[6];
        int modelNumber = 0;
        if (pROS[0] == NULL)
        {
            for (int k=0;k<8;k++)
            {
                pROS[k] = new float[N];
            }
        }
        qDebug()<<pROS[0][N-1]<<"\n";

        for(long i=0;i<N;i++)
        {
            modelNumber = (int) (*vecRaster[0])[i];
            //adjust moistures(from percentages to decimals)
            // moisture indexs:
            moisture[0] = 0.01*(*vecRaster[6])[i];
            moisture[1] = 0.01*(*vecRaster[7])[i];
            moisture[2] = 0.01*(*vecRaster[8])[i];
            moisture[3] = 0.01*(*vecRaster[8])[i];
            moisture[4] = 0.01*(*vecRaster[9])[i];
            moisture[5] = 0.01*(*vecRaster[10])[i];
            double windSpeed = (*vecRaster[4])[i];
            double windDirection = (*vecRaster[5])[i];
            double slope = (*vecRaster[3])[i];
            double aspect = (*vecRaster[2])[i];
    //        cout<<moisture[0]<<endl;
            Fire_SpreadNoWindNoSlope(catalog, modelNumber, moisture);
            Fire_SpreadWindSlopeMax(catalog,modelNumber,windSpeed,windDirection,slope,aspect);

            if(i==0)
            {
                for(int j=0;j<6;j++)
                    cout<<moisture[j]<<endl;
                cout<<windDirection<<endl;
                cout<<windSpeed<<endl<<slope<<endl<<aspect<<endl;
            }
            for(int n=0;n<8;n++)
            {
                Fire_SpreadAtAzimuth(catalog,modelNumber,nAzm[n],FIRE_NONE);
                //Fire_SpreadAtAzimuth(catalog,modelNumber,nAzm[n],FIRE_NONE);
                // spread rates from ft/min to m/min
                pROS[n][i] = 0.3048*(float)Fuel_SpreadAny(catalog, modelNumber);
                if(i==0)
                    cout<<i<<" "<<nAzm[n]<<" " <<pROS[n][i]<<endl;

            }
        }
        return 0;

    }
    catch (exception &e)
    {
        qDebug()<<e.what()<<"\n";
    }

}

int CTriggers::createRasterNetwork()
{
    try
    {
        if (nRows*nCols>0)
        {
            cout<<"creating raster network"<<endl;
            long nCellNum = nRows*nCols;
            pArcList = new float*[nCellNum];
            // allocate memory for the raster network
            for (long i = 0;i<nCellNum;i++)
            {
                pArcList[i] = new float[8]; // 8 directions (from north, clockwise, 0-7)
                for(int j = 0;j<8;j++)
                {
                    pArcList[i][j] =-1; //initialize all cost values to -1
                }
            }

            float res = cellSize/2.0;
            float resD = sqrt(2.0)*cellSize/2.0;

            cout<<res<<resD<<endl;

            for (int i =0;i<nRows;i++)
            {
                for (int j =0;j<nCols;j++)
                {
                    long n = i*nCols + j;
                    //north 0
                    if (i > 0)
                    {
                        //if (pROS[4][n]!=0 && pROS[4][n-nCols]!=0)
                        if (pROS[0][n]>0 && pROS[0][n-nCols]>0)
                        {
                            pArcList[n][0] = res/pROS[0][n] + res/pROS[0][n-nCols];
                            //cout<<pArcList[n][0]<<endl;
                        }
                        else
                        {
                            pArcList[n][0] = TMAXCOST;
                        }

                    }
                    //northeast 1
                    if (i>0 && j>0)
                    {
                        //if(pROS[5][n]!=0 && pROS[5][n-nCols+1]!=0)
                        if(pROS[1][n]>0 && pROS[1][n-nCols+1]>0)
                        {
                            pArcList[n][1] = resD/pROS[1][n] + resD/pROS[1][n-nCols+1];
                        }
                        else
                        {
                            pArcList[n][1] = TMAXCOST;
                        }
                    }
                    //east 2
                    if (j<nCols-1)
                    {
                        //if (pROS[6][n]!=0 && pROS[6][n+1]!=0)
                        if (pROS[2][n]>0 && pROS[2][n+1]>0)
                        {
                            pArcList[n][2] = res/pROS[2][n] + res/pROS[2][n+1];
                        }
                        else
                        {
                            pArcList[n][2] = TMAXCOST;
                        }
                    }
                    //southeast 3
                    if (i<nRows-1 && j<nCols-1)
                    {
                        //if (pROS[7][n]!=0 && pROS[7][n+nCols+1]!=0)
                        if (pROS[3][n]>0 && pROS[3][n+nCols+1]>0)
                        {
                            pArcList[n][3] = resD/pROS[3][n] + resD/pROS[3][n+nCols+1];

                        }
                        else
                        {
                            pArcList[n][3] = TMAXCOST;
                        }

                    }
                    //south 4
                    if (i<nRows-1)
                    {
                        //if (pROS[0][n]!=0 && pROS[0][n+nCols]!=0)
                        if (pROS[4][n]>0 && pROS[4][n+nCols]>0)
                        {
                            pArcList[n][4] = res/pROS[4][n] + res/pROS[4][n+nCols];
                        }
                        else
                        {
                            pArcList[n][4] = TMAXCOST;
                        }
                    }
                    //southwest 5
                    if (i<nRows-1 && j>0)
                    {
                        //if (pROS[1][n]!=0 && pROS[1][n+nCols-1]!=0)
                        if (pROS[5][n]>0 && pROS[5][n+nCols-1]>0)
                        {
                            pArcList[n][5] = resD/pROS[5][n] + resD/pROS[5][n+nCols-1];
                        }
                        else
                        {
                            pArcList[n][5] = TMAXCOST;
                        }
                    }
                    //west 6
                    if (j>0)
                    {
                        //if (pROS[2][n]!=0 && pROS[2][n-1]!=0)
                        if (pROS[6][n]>0 && pROS[6][n-1]>0)
                        {
                            pArcList[n][6] = res/pROS[6][n] + res/pROS[6][n-1];
                        }
                        else
                        {
                            pArcList[n][6] =  TMAXCOST;
                        }
                    }
                    //northwest 7
                    if (i>0 && j>0)
                    {
                        //if (pROS[3][n]!=0 && pROS[3][n-nCols-1]!=0)
                        if (pROS[7][n]>0 && pROS[7][n-nCols-1]>0)
                        {
                            pArcList[n][7] = resD/pROS[7][n] + resD/pROS[7][n-nCols-1];
                        }
                        else
                        {
                            pArcList[n][7] = TMAXCOST;
                        }
                    }

                }
            }//end for

            //delete the ROS data
            if (pROS[0]!=NULL)
            {
                for (int i = 0;i<8;i++)
                {
                    delete pROS[i];
                    pROS[i] = NULL;
                }
            }

            cout<<"creating raster network done"<<endl;

        }//end if

    }
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }


    cout<<"raster network created"<<endl;
    return 0;
}
// calculate trigger buffer (Dijkstra algorithm)
int CTriggers::Dijkstra(long source, int time)
{
    try
    {
        long nCellNum = nRows*nCols;
        if (nCellNum>0)
        {
            bool * pSelectedList = new bool[nCellNum];
            float * pMinCostList = new float[nCellNum];

            for (long i = 0;i<nCellNum;i++)
            {
                pSelectedList[i] = false;
                pMinCostList[i] = TMAXCOST;
            }


            set<long> adjList;
            adjList.insert(source);

            for(int i=0;i<8;i++)
            {
                long nodeID = getNeighborID(source,i);
                pMinCostList[nodeID] = pArcList[source][i];
                //cout<<nodeID<<": "<<pArcList[source][i]<<endl;
                adjList.insert(nodeID);
            }
            long v = source;
            pSelectedList[v] = true;
            pMinCostList[v] = 0.0;
            float travelTime = 0.0;

            //start minimum path algorithm iteration
            long n =0;
            while(n<nCellNum-1 && travelTime<=time)
            {
                int node = -1;
                float minCost = TMAXCOST;

                for(set<long>::iterator it = adjList.begin();it!=adjList.end();++it)
                {
                    if (!pSelectedList[*it])
                    {
                        if (pMinCostList[*it]<minCost)
                        {
                            node = *it;
                            minCost = pMinCostList[*it];
                            //cout<<node<<endl;

                        }
                    }
                }// end for

                if (minCost<=time)
                {
                    pSelectedList[node] = true;
                }
                else
                {
                    break;
                }

                for (int i = 0;i<8;i++)
                {
                    int nodeID = getNeighborID(node,i);
                    if(nodeID<0)
                        continue;
                    adjList.insert(nodeID);
                }
                travelTime = minCost;
                n++;

                for (set<long>::iterator it = adjList.begin();it!=adjList.end();++it)
                {
                    if (!pSelectedList[*it])
                    {
                        //cout<<"it: "<<*it<<endl;
                        float cost = arcCost(node,*it);
                        if (minCost + cost < pMinCostList[*it])
                        {
                            pMinCostList[*it] = minCost + cost;
                        }
                    }
                }
                //for (int j =0;j<nCellNum;j++)
                //{
                //	if (!pSelectedList[j])
                //	{
                //		float cost = arcCost(node,j);
                //		cout<<cost<<endl;
                //		if (minCost + cost < pMinCostList[j])
                //		{
                //			pMinCostList[j] = minCost + cost;
                //		}
                //	}
                //}

            //}//end for
            }//end while

            //cout<<"travel time: "<<travelTime<<endl;

            //Union the buffer to the whole trigger buffer
            for (long i=0;i<nCellNum;i++)
            {
                pTriggerBuffer[i] = pTriggerBuffer[i]||pSelectedList[i];
            }


            if (pSelectedList!=NULL)
            {
                delete [] pSelectedList;
            }
            if (pMinCostList!=NULL)
            {
                delete [] pMinCostList;
            }

        }//end if

        return 0;
    }//end try
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }
}

long CTriggers::getNeighborID(long node, int direction)
{
    if ( nRows>0 && nCols>0)
    {
        long nodeID = -1;
        switch (direction)
        {
        case 0:
            nodeID = node - nCols;
            break;
        case 1:
            nodeID = node-nCols+1;
            break;
        case 2:
            nodeID = node+1;
            break;
        case 3:
            nodeID = node+nCols+1;
            break;
        case 4:
            nodeID = node+nCols;
            break;
        case 5:
            nodeID = node+nCols-1;
            break;
        case 6:
            nodeID = node-1;
            break;
        case 7:
            nodeID = node-nCols-1;
            break;
        default:
            break;
        }
        return nodeID;
    }
    else
    {
        return -1;
    }

}

float CTriggers::arcCost(long node1, long node2)
{
    long nCellNum = nRows*nCols;

    float cost = TMAXCOST;
    float offset = node1- node2;
    if (node1<0||node2<0||node1>=nCellNum||node2>=nCellNum)
    {
        return -1;
    }
    if (abs(offset)>nCols+1)
    {
        return cost;
    }
    if (offset == nCols)
    {
        cost = pArcList[node1][0];
    }
    else if (offset == nCols-1)
    {
        cost = pArcList[node1][1];
    }
    else if(offset==-1)
    {
        cost = pArcList[node1][2];
    }
    else if (offset== -nCols-1)
    {
        //cout<<pArcList[3][node1]<<endl;
        cost = pArcList[node1][3];
    }
    else if(offset==-nCols)
    {
        cost = pArcList[node1][4];
    }
    else if(offset == -nCols+1)
    {
        cost = pArcList[node1][5];
    }
    else if (offset == 1)
    {
        cost = pArcList[node1][6];
    }
    else if(offset == nCols +1)
    {
        cost = pArcList[node1][7];
    }
    return cost;
}
// read input geogaphic feature from a asc raster file
// calcualte the cell IDs and store them in the array
int CTriggers::readInputCellFile(string strFileName)
{
    try
    {
        //clear the cell array
        if (cellArray.size()>0)
        {
            cellArray.clear();
        }
        ifstream cellFile(strFileName.c_str());
        if (cellFile.is_open())
        {
            int n =0;
            cellFile>>n;
            int i =0, cell =0;
            while (i<n && !cellFile.eof())
            {
                cellFile>>cell;
                //NOTE:the cell IDs start from 0 in this C++ implementation
                //while it starts from 1 in the input file
                cell = cell -1;

                cellArray.push_back(cell);
                i++;
            }

        }
        cellFile.close();
        cout<<"total number of input cells in the cell file: "<<cellArray.size()<<endl;
        //calculate all the boundary cells and store their IDs in a new array
        if (boundaryCellArray.size()>0)
        {
            boundaryCellArray.clear(); //clear the boundary cell array
        }

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
                else //judge the eight neighbor cells
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
    }
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}

int CTriggers::getBoundaryCells(string strFileName)
{
    try
    {   // clear the cell array if it is not empty
        if(cellArray.size()>0)
        {
            cellArray.clear();
        }

        CRasterTriggerInput triggerInput (strFileName.c_str());
        triggerInput.readData();

        boundaryCellArray = triggerInput.getInputRasterFeature();

        for(vector<long>::iterator it = boundaryCellArray.begin();it!= boundaryCellArray.end();it++)
        {
            qDebug()<<*it;
        }
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }
}

int CTriggers::calculateTriggerBuffer(long cellID, int time)
{
    if(pTriggerBuffer == NULL)
    {
        long N = nRows*nCols;
        if(N>0)
        {
            pTriggerBuffer = new bool[N];
            for(long i=0;i<N;i++)
            {
                pTriggerBuffer[i] = false;
            }
        }
    }
    if (cellArray.size()>0)
    {
        //for (vector<int>::iterator it = cellArray.begin();it!=cellArray.end();++it)
        for (int i =0;i<boundaryCellArray.size();i++)
        {
            Dijkstra(boundaryCellArray[i],time);
//			cout<<"Thread ID: "<<omp_get_thread_num()<<"  cell ID: "<<boundaryCellArray[i]<<endl;

        }
    }
    else
    {
        Dijkstra(cellID,time);
        cout<<"cell ID: "<<cellID<<endl;

    }
    return 0;
}

int CTriggers::writeTriggerBuffer(string strFileName)
{
    ofstream outFile(strFileName.c_str());
    if (outFile.is_open())
    {
        for(int i=0;i<nRows;i++)
        {
            for(int j=0;j<nCols;j++)
            {
                long n = i*nCols +j;
                string str = " ";
                //outFile<<pSelectedList[n]?1:0;
                outFile<<pTriggerBuffer[n]?1:0;
                outFile<<str;
            }
            outFile<<endl;
        }
    }
    outFile.close();
    cout<<"trigger file written to "<<strFileName<<endl;

    return 0;
}
