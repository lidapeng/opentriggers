#ifndef CPROJECTFILE_H
#define CPROJECTFILE_H
#include <string>
#include <iostream>
//#include "rasternet.h"
using namespace std;
// CProjectFile stores all relevant file information for input data in a specific project file
class CProjectFile
{
private:
    std::string strProjFileName;
    std::string  mFileDEM;
    std::string  mFileSlope;
    std::string  mFileAspect;
    string mFileFuel;
    double mWindSpeed;
    double mWindDirection;
    double m1hMoisture;
    double m10hMoisture;
    double m100hMoisture;
    double mherbMoisture;
    double mwoodMoisture;

    bool bIsProjLoaded;
   // ASCFileHeader mFileHeader;
public:
    CProjectFile();
    CProjectFile(std::string fileName);
    std::string getProjFileName();
    void setProjFileName(std::string fileName);
    friend std::ostream& operator<<(std::ostream& os, const CProjectFile& p);
    friend std::istream& operator>>(std::istream&is, CProjectFile& p);
    std::string getMFileDEM() const;
    void setMFileDEM(const std::string &value);
    std::string getMFileSlope() const;
    void setMFileSlope(const std::string &value);
    std::string getMFileAspect() const;
    void setMFileAspect(const std::string &value);
    string getMFileFuel() const;
    void setMFileFuel(const string &value);
    double getMWindSpeed() const;
    void setMWindSpeed(double value);
    double getMWindDirection() const;
    void setMWindDirection(double value);
   // ASCFileHeader getMFileHeader() const;
    //void setMFileHeader(const ASCFileHeader &value);
    double getM1hMoisture() const;
    void setM1hMoisture(double value);
    double getM10hMoisture() const;
    void setM10hMoisture(double value);
    double getM100hMoisture() const;
    void setM100hMoisture(double value);
    double getMherbMoisture() const;
    void setMherbMoisture(double value);
    double getMwoodMoisture() const;
    void setMwoodMoisture(double value);

    bool getBIsProjLoaded() const;
    void setBIsProjLoaded(bool value);
};

#endif // CPROJECTFILE_H
