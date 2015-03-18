#include "rasternet.h"

// constructor
CRasterNet::CRasterNet(void)
{
	nRows = 0;
	nCols = 0;
	nCellNum = 0;
	cellRes = 0.0;
	//pSelectedList = NULL;
	//pMinCostList = NULL;
	pArcList = NULL;

	pTriggerBuffer = NULL;
	cellArray.clear();
	boundaryCellArray.clear();
	pHeader = NULL;
	for(int i =0;i<8;i++)
		pROSData[i] = NULL;

    pDEM = NULL;
    pSlope = NULL;
    pAspect = NULL;
    pFuel = NULL;
    pWindSpeed = NULL;
    pWindDirect = NULL;
    p1hMoisture = NULL;
    p10hMoisture = NULL;
    p100hMoisture = NULL;
    pHerbMoisture = NULL;
    pWoodMoisture = NULL;
}


CRasterNet::~CRasterNet(void)
{
    // delete all input raster data
    deleteRasterData();

	if (pHeader != NULL)
	{
		delete pHeader;
	}
	if (pROSData[0]!=NULL)
	{
		for (int i = 0;i<8;i++)
		{
			delete pROSData[i];
			pROSData[i] = NULL;
		}
	}
	//if (pSelectedList!=NULL)
	//{
	//	delete [] pSelectedList;
	//}
	//if (pMinCostList !=NULL)
	//{
	//	delete [] pMinCostList;
	//}
	if (pArcList!=NULL)
	{
		for(int i = 0; i<nCellNum;i++)
			delete [] pArcList[i];
		delete [] pArcList;
	}

	if (pTriggerBuffer!=NULL)
	{
		delete [] pTriggerBuffer;
	}

}

int CRasterNet::getNeighborID(int node,int direction)
{
	if (nCellNum>0 && nRows>0 && nCols>0)
	{
		int nodeID = -1;
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

float CRasterNet::arcCost(int node1,int node2)
{
	float cost = MAXCOST;
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


//read an ASC file
int CRasterNet::readROSRasterData(string strFileName,float** ptr[])
{
	try
	{
		if (!pHeader)
		{
			pHeader = new ASCFileHeader();
		}
		FILE *fpin;
		int rows =0, cols = 0;
		//cols = 0;
		float val = 0;
		char temp[20], temp2[20];
		float res =0.0, noData = 0.0;
		double xll = 0.0, yll=0.0;
		//printf("\nReading FLAMMAP input data:\n");
		cout<<"\nReading FLAMMAP input data: "<<strFileName<<endl;

		if ((fpin = fopen(strFileName.c_str(), "r")) != NULL)
		{
			
			fscanf(fpin, "%s %d\n", temp, &cols);
			pHeader->setCols(cols);
			fscanf(fpin, "%s %d\n", temp, &rows);
			pHeader->setRows(rows);
			fscanf(fpin, "%s %lf\n", temp, &xll);
			pHeader->setXLLCorner(xll);
			fscanf(fpin, "%s %lf\n", temp, &yll);
			pHeader->setYLLCorner(yll);
			fscanf(fpin, "%s %f\n", temp, &res);
			pHeader->setCellSize(res);
			fscanf(fpin, "%s %f\n", temp, &noData);
			pHeader->setNoDataValue(noData);

			cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;

			for (int k = 0;k<8;k++)
			{
				for(int i = 0;i<pHeader->getRows();i++)
				{
					for(int j =0;j<pHeader->getCols();j++)
					{
						fscanf(fpin,"%f",&ptr[k][i][j]);
					}
				}
			}
		}

		fclose(fpin);
			



		//ifstream inFile(strFileName);
		//int nRowCount = 0;

		//if (inFile.is_open())
		//{
		//	string strLine = "";
		//	inFile.seekg(0,fstream::end);
		//	ifstream::pos_type end_mark = inFile.tellg();
		//	inFile.seekg(0,fstream::beg);
		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		int nCol = 0;

		//		if (!(iss>>strTemp>>nCol))
		//		{
		//			return 1;
		//		}
		//		pHeader->setCols(nCol);
		//		cout<<"*********"<<strTemp<<" "<<nCol<<endl;
		//	}
		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		int nRow = 0;

		//		if (!(iss>>strTemp>>nRow))
		//		{
		//			return 1;
		//		}
		//		pHeader->setRows(nRow);
		//		cout<<"*********"<<strTemp<<" "<<nRow<<endl;
		//	}

		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		double xll = 0.0;
		//		if (!(iss>>strTemp>>xll))
		//		{
		//			return 1;
		//		}

		//		pHeader->setXLLCorner(xll);
		//		cout<<"*********"<<strTemp<<" "<<xll<<endl;
		//	}

		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		double yll = 0.0;
		//		if (!(iss>>strTemp>>yll))
		//		{
		//			return 1;
		//		}
		//		pHeader->setYLLCorner(yll);
		//		cout<<"*********"<<strTemp<<" "<<yll<<endl;
		//	}

		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		float resolution = 0.0;
		//		if (!(iss>>strTemp>>resolution))
		//		{
		//			return 1;
		//		}
		//		pHeader->setCellSize(resolution);
		//		cout<<"*********"<<strTemp<<" "<<resolution<<endl;
		//	}
		//	if (getline(inFile,strLine))
		//	{
		//		istringstream iss(strLine);
		//		string strTemp;
		//		float noData = 0.0;
		//		if (!(iss>>strTemp>>noData))
		//		{
		//			return 1;
		//		}
		//		pHeader->setNoDataValue(noData);
		//		cout<<"*********"<<strTemp<<" "<<noData<<endl;
		//	}


			//while(inFile && inFile.tellg()!=end_mark && getline(inFile,strLine))
			//{
			//	//if (!getline(inFile,strLine))
			//	//{
			//	//	return 1;
			//	//}
			//	istringstream iss(strLine);
			//	string strTemp;
			//	if (0 == nRowCount)
			//	{
			//		int nCol = 0;

			//		if (!(iss>>strTemp>>nCol))
			//		{
			//			return 1;
			//		}

			//		pHeader->setCols(nCol);
			//		cout<<"*********"<<strTemp<<" "<<nCol<<endl;

			//	}
			//	if (1 == nRowCount)
			//	{
			//		int nRow = 0;

			//		if (!(iss>>strTemp>>nRow))
			//		{
			//			return 1;
			//		}
			//		pHeader->setRows(nRow);
			//		cout<<"*********"<<strTemp<<" "<<nRow<<endl;
			//	}
			//	if (2 == nRowCount)
			//	{
			//		float xll = 0.0;
			//		if (!(iss>>strTemp>>xll))
			//		{
			//			return 1;
			//		}

			//		pHeader->setXLLCorner(xll);
			//		cout<<"*********"<<strTemp<<" "<<xll<<endl;
			//	}
			//	if (3 == nRowCount)
			//	{
			//		float yll = 0.0;
			//		if (!(iss>>strTemp>>yll))
			//		{
			//			return 1;
			//		}
			//		pHeader->setYLLCorner(yll);
			//		cout<<"*********"<<strTemp<<" "<<yll<<endl;
			//	}
			//	if (4 == nRowCount)
			//	{

			//		float resolution = 0.0;
			//		if (!(iss>>strTemp>>resolution))
			//		{
			//			return 1;
			//		}
			//		pHeader->setCellSize(resolution);
			//		cout<<"*********"<<strTemp<<" "<<resolution<<endl;
			//	}
			//	if (5 == nRowCount)
			//	{
			//		float noData = 0.0;
			//		if (!(iss>>strTemp>>noData))
			//		{
			//			return 1;
			//		}
			//		pHeader->setNoDataValue(noData);
			//		cout<<"*********"<<strTemp<<" "<<noData<<endl;

			//	}
			//	//if (nRowCount>5)
			//	//{
			//	//	break;
			//	//}
			//	if (nRowCount>5)
			//	{
			//		float temp = 0.0;

			//		for (int i =0;i<pHeader->getCols();i++)
			//		{
			//			iss.precision(5);
			//			iss>>temp;
			//			if(nRowCount<106)
			//				ptr[nRowCount-6][i]=temp;

			//		}

			//	}
			//	nRowCount++;
			//}
			//for(int i=0;i<pHeader->getRows();i++)
			//{
			//	//if (inFile && inFile.tellg()!=end_mark && getline(inFile,strLine))
			//	if (!getline(inFile,strLine))
			//	{
			//		return 1;
			//	}
			//	istringstream iss(strLine);

			//	float temp = 0.0;
			//	for (int j =0;i<pHeader->getCols();j++)
			//	{

			//		iss>>temp;
			//		ptr[i][j]=temp;

			//	}


			////	nRowCount++;


			//}


			cout<<"\nReading FLAMMAP input data: "<<strFileName<<" done"<<endl;

			return 0;

	}
	catch (exception &e)
	{
		cout<<e.what()<<endl;
	}
}
int CRasterNet::readROSRasterData(string strFileName,float* ptr[])
{
    try
    {

        if (!pHeader)
        {
            pHeader = new ASCFileHeader();
        }

		FILE *fpin;
		int rows =0, cols = 0;
		//cols = 0;
		float val = 0;
		char temp[20], temp2[20];
		float res =0.0, noData = 0.0;
		double xll = 0.0, yll=0.0;

		cout<<"\nReading FLAMMAP input data: "<<strFileName<<endl;

		if ((fpin = fopen(strFileName.c_str(), "r")) != NULL)
		{

			fscanf(fpin, "%s %d\n", temp, &cols);
			
			fscanf(fpin, "%s %d\n", temp, &rows);
			
			fscanf(fpin, "%s %lf\n", temp, &xll);
			
			fscanf(fpin, "%s %lf\n", temp, &yll);
			
			fscanf(fpin, "%s %f\n", temp, &res);
			
			fscanf(fpin, "%s %f\n", temp, &noData);

			pHeader->setCols(cols);
			pHeader->setRows(rows);
			pHeader->setXLLCorner(xll);
			pHeader->setYLLCorner(yll);
			pHeader->setCellSize(res);
			pHeader->setNoDataValue(noData);

			//cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;

			for (int k = 0;k<8;k++)
			{
				for(int i = 0;i<pHeader->getRows()*pHeader->getCols();i++)
				{
					fscanf(fpin,"%f",&ptr[k][i]);
					//for(int j =0;j<pHeader->getCols();j++)
					//{
					//	fscanf(fpin,"%f",&ptr[k][i][j]);
					//}
				}
			}
		}

		fclose(fpin);

		cout<<"\nReading FLAMMAP input data: "<<strFileName<<" done"<<endl;

		return 0;



	}
	catch (exception &e)
	{
		cout<<e.what()<<endl;
	}
}

int CRasterNet::readROSRasterData(string strFileName)
{
	try
	{

		if (!pHeader)
		{
			pHeader = new ASCFileHeader();
		}

		FILE *fpin;
		int rows =0, cols = 0;
		//cols = 0;
		float val = 0;
		char temp[20], temp2[20];
		float res =0.0, noData = 0.0;
		double xll = 0.0, yll=0.0;
		cout<<"\nReading FLAMMAP input data: "<<strFileName<<endl;

		if ((fpin = fopen(strFileName.c_str(), "r")) != NULL)
		{

			fscanf(fpin, "%s %d\n", temp, &cols);

			fscanf(fpin, "%s %d\n", temp, &rows);

			fscanf(fpin, "%s %lf\n", temp, &xll);

			fscanf(fpin, "%s %lf\n", temp, &yll);

			fscanf(fpin, "%s %f\n", temp, &res);

			fscanf(fpin, "%s %f\n", temp, &noData);

			pHeader->setCols(cols);
			pHeader->setRows(rows);
			pHeader->setXLLCorner(xll);
			pHeader->setYLLCorner(yll);
			pHeader->setCellSize(res);
			pHeader->setNoDataValue(noData);

			//cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;

			nRows = pHeader->getRows();
			nCols = pHeader->getCols();
			nCellNum = nRows*nCols;
			cellRes = res;

			if (pROSData[0] == NULL)
			{
				for (int k=0;k<8;k++)
				{
					pROSData[k] = new float[nCellNum];
				}
			}

			for (int k = 0;k<8;k++)
			{
				for(int i = 0;i<nCellNum;i++)
				{
					fscanf(fpin,"%f",&pROSData[k][i]);

				}
			}
		}

		fclose(fpin);

		cout<<"\nReading FLAMMAP input data: "<<strFileName<<" done"<<endl;

		return 0;

	}
	catch (exception &e)
	{
		cout<<e.what()<<endl;
	}
}
//read the cell file in the WUIVAC configuration file
int CRasterNet::readCellFile(string strCellFile)
{
	try
	{	
		//read all the cell IDs from the cell file to the cell array cellArray
		if (cellArray.size()>0)
		{
			cellArray.clear();
		}
		ifstream cellFile(strCellFile.c_str());
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
		
		if (nCellNum>0 && nRows>0 && nCols>0)
		{
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
			for (vector<int>::iterator it = cellArray.begin();it!=cellArray.end();++it)
			{
				//cout<<"value: "<<*it<<endl;
				pCellData[*it]= true; 
			}
			//extract the boundary cells
			for (vector<int>::iterator it = cellArray.begin();it!=cellArray.end();++it)
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

int CRasterNet::createRasterNetwork()
{
	try
	{
		if (nCellNum>0)
		{
			//cout<<"nCellNum: "<<nCellNum<<endl;
			cout<<"creating raster network"<<endl;

			pArcList = new float*[nCellNum];
			for (int i = 0;i<nCellNum;i++)
			{
				pArcList[i] = new float[8]; // 8 directions (from north, clockwise, 0-7)
				for(int j = 0;j<8;j++)
				{
					pArcList[i][j] =-1; //initialize all cost values to -1
				}
			}

			float res = cellRes/2.0;
			float resD = sqrt(2.0)*cellRes/2.0;

			cout<<res<<resD<<endl;

			for (int i =0;i<nRows;i++)
			{
				for (int j =0;j<nCols;j++)
				{
					int n = i*nCols + j;
					//north 0 reverse 4
					if (i > 0)
					{
						//if (pROSData[4][n]!=0 && pROSData[4][n-nCols]!=0)
						if (pROSData[4][n]>0 && pROSData[4][n-nCols]>0)
						{
							pArcList[n][0] = res/pROSData[4][n] + res/pROSData[4][n-nCols];
							//cout<<pArcList[n][0]<<endl;
						}
						else
						{
							pArcList[n][0] = MAXCOST;
						}
						
					}
					//northeast 1 reverse 5
					if (i>0 && j>0)
					{
						//if(pROSData[5][n]!=0 && pROSData[5][n-nCols+1]!=0)
						if(pROSData[5][n]>0 && pROSData[5][n-nCols+1]>0)
						{
							pArcList[n][1] = resD/pROSData[5][n] + resD/pROSData[5][n-nCols+1];
						}
						else
						{
							pArcList[n][1] = MAXCOST;
						}
					}
					//east 2 reverse 6
					if (j<nCols-1)
					{
						//if (pROSData[6][n]!=0 && pROSData[6][n+1]!=0)
						if (pROSData[6][n]>0 && pROSData[6][n+1]>0)
						{
							pArcList[n][2] = res/pROSData[6][n] + res/pROSData[6][n+1];
						}
						else
						{
							pArcList[n][2] = MAXCOST;
						}
					}
					//southeast 3 reverse 7
					if (i<nRows-1 && j<nCols-1)
					{
						//if (pROSData[7][n]!=0 && pROSData[7][n+nCols+1]!=0)
						if (pROSData[7][n]>0 && pROSData[7][n+nCols+1]>0)
						{
							pArcList[n][3] = resD/pROSData[7][n] + resD/pROSData[7][n+nCols+1];
							
						}
						else
						{
							pArcList[n][3] = MAXCOST;
						}

					}
					//south 4 reverse 0
					if (i<nRows-1)
					{
						//if (pROSData[0][n]!=0 && pROSData[0][n+nCols]!=0)
						if (pROSData[0][n]>0 && pROSData[0][n+nCols]>0)
						{
							pArcList[n][4] = res/pROSData[0][n] + res/pROSData[0][n+nCols];
						}
						else
						{
							pArcList[n][4] = MAXCOST;
						}
					}
					//southwest 5 reverse 1
					if (i<nRows-1 && j>0)
					{
						//if (pROSData[1][n]!=0 && pROSData[1][n+nCols-1]!=0)
						if (pROSData[1][n]>0 && pROSData[1][n+nCols-1]>0)
						{
							pArcList[n][5] = resD/pROSData[1][n] + resD/pROSData[1][n+nCols-1];
						} 
						else
						{
							pArcList[n][5] = MAXCOST;
						}
					}
					//west 6 reverse 2
					if (j>0)
					{
						//if (pROSData[2][n]!=0 && pROSData[2][n-1]!=0)
						if (pROSData[2][n]>0 && pROSData[2][n-1]>0)
						{
							pArcList[n][6] = res/pROSData[2][n] + res/pROSData[2][n-1];
						} 
						else
						{
							pArcList[n][6] =  MAXCOST;
						}
					}
					//northwest 7 reverse 3
					if (i>0 && j>0)
					{
						//if (pROSData[3][n]!=0 && pROSData[3][n-nCols-1]!=0)
						if (pROSData[3][n]>0 && pROSData[3][n-nCols-1]>0)
						{
							pArcList[n][7] = resD/pROSData[3][n] + resD/pROSData[3][n-nCols-1];
						}
						else
						{
							pArcList[n][7] = MAXCOST;
						}
					}

				}
			}//end for
			
			//delete the ROS data
			if (pROSData[0]!=NULL)
			{
				for (int i = 0;i<8;i++)
				{
					delete pROSData[i];
					pROSData[i] = NULL;
				}
			}
			//initialize the final trigger buffer
			if (!pTriggerBuffer)
			{
				pTriggerBuffer = new bool[nCellNum];
				for (int i = 0;i<nCellNum;i++)
				{
					pTriggerBuffer[i] = false;
				}
			}
			cout<<"creating raster network done"<<endl;

		}//end if

	}
	catch (exception &e)
	{
		cout<<e.what()<<endl;
	}


	//cout<<"raster network created"<<endl;
	return 0;
}

int CRasterNet::Dijkstra(int source, int time)
{
	try
	{
		if (nCellNum>0)
		{
			bool * pSelectedList = new bool[nCellNum];
			float * pMinCostList = new float[nCellNum];

			for (int i = 0;i<nCellNum;i++)
			{
				pSelectedList[i] = false;
				pMinCostList[i] = MAXCOST;
			}

			
			set<int> adjList;
			adjList.insert(source);

			for(int i=0;i<8;i++)
			{
				int nodeID = getNeighborID(source,i);
				pMinCostList[nodeID] = pArcList[source][i];
				//cout<<nodeID<<": "<<pArcList[source][i]<<endl;
				adjList.insert(nodeID);
			}
			int v = source;
			pSelectedList[v] = true;
			pMinCostList[v] = 0.0;
			float travelTime = 0.0;
			
			//start minimum path algorithm iteration
			//for(int i =0;i<nCellNum-1;i++)
			//{
			int n =0;
			while(n<nCellNum-1 && travelTime<=time)
			{
				int node = -1;
				float minCost = MAXCOST;

				for(set<int>::iterator it = adjList.begin();it!=adjList.end();++it)
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
				}
				//}
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
				//if (n<50)
				//{
				//	cout<<"source: "<<source<<endl;
				//	cout<<"node: "<<node<<endl;
				//	cout<<n<<": "<<travelTime<<endl;
				//}

					//node = getNeighborID(node,j);
					//if (!pSelectedList[node])
					//{
					//	if(pArcList[node][j]<minCost)
					//	{
					//		v = node;
					//		minCost = pArcList[node][j];
					//	}
					//}

				for (set<int>::iterator it = adjList.begin();it!=adjList.end();++it)
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
//			#pragma omp critical
//			{
				for (int i=0;i<nCellNum;i++)
				{
					pTriggerBuffer[i] = pTriggerBuffer[i]||pSelectedList[i];
				}
//			}


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

int CRasterNet::calculateTriggerBufer(int cellID,int time)
{
	if (cellArray.size()>0)
	{
//		int a = omp_get_max_threads();
//		cout<<"maximum number of threads: "<<a<<endl;
//		omp_set_num_threads(a);
//		double startTime = omp_get_wtime();
//		#pragma omp parallel for
		//for (vector<int>::iterator it = cellArray.begin();it!=cellArray.end();++it)
		for (int i =0;i<boundaryCellArray.size();i++)
		{
			Dijkstra(boundaryCellArray[i],time);
//			#pragma omp critical
//			cout<<"Thread ID: "<<omp_get_thread_num()<<"  cell ID: "<<boundaryCellArray[i]<<endl;

		}
//		double endTime = omp_get_wtime();
//		cout<<"\ntotal time: "<<endTime-startTime<<endl;
	}
	else
	{
		Dijkstra(cellID,time);
		cout<<"cell ID: "<<cellID<<endl;
		
	}
    return 0;
}

void CRasterNet::deleteRasterData()
{
    try
    {
        if(pDEM!=NULL)
        {
            delete [] pDEM;
        }
        if(pSlope!=NULL)
        {
            delete [] pSlope;
        }
        if(pAspect!=NULL)
        {
            delete [] pAspect;
        }
        if(pFuel!=NULL)
        {
            delete [] pFuel;
        }
        if(pWindSpeed!=NULL)
        {
            delete [] pWindSpeed;
        }
        if(pWindDirect!=NULL)
        {
            delete [] pWindDirect;
        }
        if(p1hMoisture!=NULL)
        {
            delete [] p1hMoisture;
        }
        if(p10hMoisture!=NULL)
        {
            delete [] p10hMoisture;
        }
        if(p100hMoisture!=NULL)
        {
            delete [] p100hMoisture;
        }
        if(pHerbMoisture!=NULL)
        {
            delete [] pHerbMoisture;
        }
        if(pWoodMoisture!=NULL)
        {
            delete [] pWoodMoisture;
        }

    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }
}

void CRasterNet::loadRasterData(const CProjectFile& prj)
{
    if(pDEM==NULL)
    {
        readRasterData(prj.getMFileDEM(),pDEM);
    }
    if(pSlope == NULL)
    {
        readRasterData(prj.getMFileSlope(),pSlope);
    }
    if(pAspect == NULL)
    {
        readRasterData(prj.getMFileAspect(),pAspect);
    }
    if(pFuel == NULL)
    {
        readRasterData(prj.getMFileFuel(),pFuel);
    }
    if(pWindSpeed == NULL)
    {
        createRasterData(prj.getMWindSpeed(),pWindSpeed);
    }
    if(pWindDirect == NULL)
    {
        createRasterData(prj.getMWindDirection(),pWindDirect);
    }
    if(p1hMoisture == NULL)
    {
        createRasterData(prj.getM1hMoisture(),p1hMoisture);
    }
    if(p10hMoisture == NULL)
    {
        createRasterData(prj.getM10hMoisture(),p10hMoisture);
    }
    if(p100hMoisture == NULL)
    {
        createRasterData(prj.getM100hMoisture(),p100hMoisture);
    }
    if(pHerbMoisture == NULL)
    {
        createRasterData(prj.getMherbMoisture(),pHerbMoisture);
    }
    if(pWoodMoisture == NULL)
    {
        createRasterData(prj.getMwoodMoisture(),pWoodMoisture);
    }
    adjustWindSpeedN(); // adjust wind speed using Wind Adjustment Factor
    // initialize variables
    nRows = pHeader->getRows();
    nCols = pHeader->getCols();
    nCellNum = nRows*nCols;
    cellRes = pHeader->getCellSize();
}

int CRasterNet::readRasterData(string strFileName, double *&ptr)
{
    try
    {
        if (!pHeader)
        {
            pHeader = new ASCFileHeader();
        }
        FILE *fpin;
        int rows =0, cols = 0;
        //cols = 0;
        float val = 0;
        char temp[20], temp2[20];
        float res =0.0, noData = 0.0;
        double xll = 0.0, yll=0.0;

        cout<<"\nReading FLAMMAP input data: "<<strFileName<<endl;

        if ((fpin = fopen(strFileName.c_str(), "r")) != NULL)
        {

            fscanf(fpin, "%s %d\n", temp, &cols);
            fscanf(fpin, "%s %d\n", temp, &rows);
            fscanf(fpin, "%s %lf\n", temp, &xll);
            fscanf(fpin, "%s %lf\n", temp, &yll);
            fscanf(fpin, "%s %f\n", temp, &res);
            fscanf(fpin, "%s %f\n", temp, &noData);
            pHeader->setCols(cols);
            pHeader->setRows(rows);
            pHeader->setXLLCorner(xll);
            pHeader->setYLLCorner(yll);
            pHeader->setCellSize(res);
            pHeader->setNoDataValue(noData);

            //cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;
            if(pHeader->getRows()>0 && pHeader->getCols()>0)
            {
                ptr = new double[pHeader->getRows()*pHeader->getCols()];
            }

            for(int i = 0;i<pHeader->getRows()*pHeader->getCols();i++)
            {
                fscanf(fpin,"%lf",&ptr[i]);
                //}
            }
        }
        fclose(fpin);
        return 0;
    }
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }
    return 0;
}

int CRasterNet::readRasterData(string strFileName, int*&ptr)
{
    try
    {
        if (!pHeader)
        {
            pHeader = new ASCFileHeader();
        }
        FILE *fpin;
        int rows =0, cols = 0;
        //cols = 0;
        float val = 0;
        char temp[20], temp2[20];
        float res =0.0, noData = 0.0;
        double xll = 0.0, yll=0.0;

        cout<<"\nReading FLAMMAP input data: "<<strFileName<<endl;

        if ((fpin = fopen(strFileName.c_str(), "r")) != NULL)
        {

            fscanf(fpin, "%s %d\n", temp, &cols);
            fscanf(fpin, "%s %d\n", temp, &rows);
            fscanf(fpin, "%s %lf\n", temp, &xll);
            fscanf(fpin, "%s %lf\n", temp, &yll);
            fscanf(fpin, "%s %f\n", temp, &res);
            fscanf(fpin, "%s %f\n", temp, &noData);
            pHeader->setCols(cols);
            pHeader->setRows(rows);
            pHeader->setXLLCorner(xll);
            pHeader->setYLLCorner(yll);
            pHeader->setCellSize(res);
            pHeader->setNoDataValue(noData);

            //cout<<pHeader->getCols()<<pHeader->getRows()<<pHeader->getXLLCorner()<<pHeader->getYLLCorner()<<pHeader->getCellSize()<<pHeader->getNoDataValue()<<endl;
            if(pHeader->getRows()>0 && pHeader->getCols()>0)
            {
                ptr = new int[pHeader->getRows()*pHeader->getCols()];
            }

            for(int i = 0;i<pHeader->getRows()*pHeader->getCols();i++)
            {
                fscanf(fpin,"%d",&ptr[i]);
                //}
            }
        }
        fclose(fpin);
        return 0;
    }
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }
    return 0;

}

int CRasterNet::createRasterData(double value, double *&ptr)
{
    try
    {
        if(pHeader->getRows()>0 && pHeader->getCols()>0)
        {
            ptr = new double[pHeader->getRows()*pHeader->getCols()];
        }

        for(int i = 0;i<pHeader->getRows()*pHeader->getCols();i++)
        {
            ptr[i] = value;
        }
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }
    return 0;
}
// use fireLib to calculate fire behavior
void CRasterNet::calculateFireBehavior()
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
    int N = pHeader->getRows()*pHeader->getCols();
    double moisture[6];
    int modelNumber = 0;
    if (pROSData[0] == NULL)
    {
        for (int k=0;k<8;k++)
        {
            pROSData[k] = new float[N];
        }
    }
    cout<<pROSData[0][N-1]<<endl;

    for(int i=0;i<N;i++)
    {
        modelNumber = pFuel[i];
        //adjust moistures(from percentages to decimals)
        moisture[0] = 0.01*p1hMoisture[i];
        moisture[1] = 0.01*p10hMoisture[i];
        moisture[2] = 0.01*p100hMoisture[i];
        moisture[3] = 0.01*p100hMoisture[i];
        moisture[4] = 0.01*pHerbMoisture[i];
        moisture[5] = 0.01*pWoodMoisture[i];
//        cout<<moisture[0]<<endl;
        Fire_SpreadNoWindNoSlope(catalog, modelNumber, moisture);
        Fire_SpreadWindSlopeMax(catalog,modelNumber,pWindSpeed[i],pWindDirect[i],pSlope[i],pAspect[i]);

        for(int n=0;n<8;n++)
        {
            Fire_SpreadAtAzimuth(catalog,modelNumber,(double)(((int)nAzm[n]+180)%360),FIRE_NONE);
            //Fire_SpreadAtAzimuth(catalog,modelNumber,nAzm[n],FIRE_NONE);
            // spread rates from ft/min to m/min
            pROSData[n][i] = 0.3048*(float)Fuel_SpreadAny(catalog, modelNumber);
            cout<<i<<" " <<pROSData[n][i]<<endl;

        }

    }

}
// adjust wind speed using Wind Adjustment Factor
// from mph (20 feet wind speed) to midflame wind speed(ft/min)
// uses the 1 decimal WAF table (not accurate)
void CRasterNet::adjustWindSpeed()
{
    if(pWindSpeed!=NULL && pFuel!=NULL && pHeader!=NULL)
    {
        for(int i =0;i<pHeader->getRows()*pHeader->getCols();i++)
        {
            if(pFuel[i]==4 || pFuel[i]==13)
            {
                pWindSpeed[i] = 0.5*88.0*pWindSpeed[i];
            }
            else if(pFuel[i]==8 || pFuel[i]==9)
            {
                pWindSpeed[i] = 0.3*88.0*pWindSpeed[i];
            }
            else
            {
                pWindSpeed[i] = 0.4*88.0*pWindSpeed[i];
            }

        }
    }
}
// adjust wind speed using Wind Adjustment Factor
// from mph (20 feet wind speed) to midflame wind speed(ft/min)
// uses the 1 decimal WAF table (not accurate)
void CRasterNet::adjustWindSpeedN()
{
    if(pWindSpeed!=NULL && pFuel!=NULL && pHeader!=NULL)
    {
        for(int i =0;i<pHeader->getRows()*pHeader->getCols();i++)
        {
            switch(pFuel[i])
            {
            case 1:
                pWindSpeed[i] = 0.36*88.0*pWindSpeed[i];
                break;
            case 2:
                pWindSpeed[i] = 0.36*88.0*pWindSpeed[i];
                break;
            case 3:
                pWindSpeed[i] = 0.44*88.0*pWindSpeed[i];
                break;
            case 4:
                pWindSpeed[i] = 0.55*88.0*pWindSpeed[i];
                break;
            case 5:
                pWindSpeed[i] = 0.42*88.0*pWindSpeed[i];
                break;
            case 6:
                pWindSpeed[i] = 0.44*88.0*pWindSpeed[i];
                break;
            case 7:
                pWindSpeed[i] = 0.44*88.0*pWindSpeed[i];
                break;
            case 8:
                pWindSpeed[i] = 0.28*88.0*pWindSpeed[i];
                break;
            case 9:
                pWindSpeed[i] = 0.28*88.0*pWindSpeed[i];
                break;
            case 10:
                pWindSpeed[i] = 0.36*88.0*pWindSpeed[i];
                break;
            case 11:
                pWindSpeed[i] = 0.36*88.0*pWindSpeed[i];
                break;
            case 12:
                pWindSpeed[i] = 0.43*88.0*pWindSpeed[i];
                break;
            case 13:
                pWindSpeed[i] = 0.46*88.0*pWindSpeed[i];
                break;
            }
        }
    }

}

bool CRasterNet::isDataLoaded()
{
    return (pDEM!=NULL && pSlope!=NULL && pAspect!=NULL && pFuel!=NULL && pWindSpeed!=NULL
            && pWindDirect!=NULL && p1hMoisture!=NULL && p10hMoisture!=NULL && p100hMoisture!=NULL
            && pHerbMoisture!=NULL && pWoodMoisture!=NULL);
}
int CRasterNet::getNRows() const
{
    return nRows;
}

void CRasterNet::setNRows(int value)
{
    nRows = value;
}
int CRasterNet::getNCols() const
{
    return nCols;
}

void CRasterNet::setNCols(int value)
{
    nCols = value;
}
bool *CRasterNet::getPTriggerBuffer() const
{
    return pTriggerBuffer;
}

void CRasterNet::setPTriggerBuffer(bool *value)
{
    pTriggerBuffer = value;
}
int CRasterNet::getNCellNum() const
{
    return nCellNum;
}

void CRasterNet::setNCellNum(int value)
{
    nCellNum = value;
}

int CRasterNet::writeTriggerBuffer(string strFileName)
{	
    ofstream outFile(strFileName.c_str());
    if (outFile.is_open())
    {
        for(int i=0;i<nRows;i++)
		{
			for(int j=0;j<nCols;j++)
			{
				int n = i*nCols +j;
				char c = ' ';
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
