#include "cprojectfile.h"


std::string CProjectFile::getMFileDEM() const
{
    return mFileDEM;
}

void CProjectFile::setMFileDEM(const std::string &value)
{
    mFileDEM = value;
}

std::string CProjectFile::getMFileSlope() const
{
    return mFileSlope;
}

void CProjectFile::setMFileSlope(const std::string &value)
{
    mFileSlope = value;
}

std::string CProjectFile::getMFileAspect() const
{
    return mFileAspect;
}

void CProjectFile::setMFileAspect(const std::string &value)
{
    mFileAspect = value;
}

string CProjectFile::getMFileFuel() const
{
    return mFileFuel;
}

void CProjectFile::setMFileFuel(const string &value)
{
    mFileFuel = value;
}

double CProjectFile::getMWindSpeed() const
{
    return mWindSpeed;
}

void CProjectFile::setMWindSpeed(double value)
{
    mWindSpeed = value;
}

double CProjectFile::getMWindDirection() const
{
    return mWindDirection;
}

void CProjectFile::setMWindDirection(double value)
{
    mWindDirection = value;
}

//ASCFileHeader CProjectFile::getMFileHeader() const
//{
//    return mFileHeader;
//}
//// set the file header
//void CProjectFile::setMFileHeader(const ASCFileHeader &value)
//{
//    mFileHeader = value;
//}

double CProjectFile::getM1hMoisture() const
{
    return m1hMoisture;
}

void CProjectFile::setM1hMoisture(double value)
{
    m1hMoisture = value;
}

double CProjectFile::getM10hMoisture() const
{
    return m10hMoisture;
}

void CProjectFile::setM10hMoisture(double value)
{
    m10hMoisture = value;
}

double CProjectFile::getM100hMoisture() const
{
    return m100hMoisture;
}

void CProjectFile::setM100hMoisture(double value)
{
    m100hMoisture = value;
}

double CProjectFile::getMherbMoisture() const
{
    return mherbMoisture;
}

void CProjectFile::setMherbMoisture(double value)
{
    mherbMoisture = value;
}

double CProjectFile::getMwoodMoisture() const
{
    return mwoodMoisture;
}

void CProjectFile::setMwoodMoisture(double value)
{
    mwoodMoisture = value;
}

bool CProjectFile::getBIsProjLoaded() const
{
    return bIsProjLoaded;
}

void CProjectFile::setBIsProjLoaded(bool value)
{
    bIsProjLoaded = value;
}
CProjectFile::CProjectFile()
{
    mWindSpeed = 0.0;
    mWindDirection = 0.0;
    m1hMoisture = 0.0;
    m10hMoisture = 0.0;
    m100hMoisture = 0.0;
    mherbMoisture = 0.0;
    mwoodMoisture = 0.0;
    bIsProjLoaded = false;
}
CProjectFile::CProjectFile(string fileName)
{
    strProjFileName = fileName;
    mWindSpeed = 0.0;
    mWindDirection = 0.0;
    m1hMoisture = 0.0;
    m10hMoisture = 0.0;
    m100hMoisture = 0.0;
    mherbMoisture = 0.0;
    mwoodMoisture = 0.0;
    bIsProjLoaded = false;
}

string CProjectFile::getProjFileName()
{
    return strProjFileName;
}

void CProjectFile::setProjFileName(string fileName)
{
    strProjFileName = fileName;
}

ostream & operator<<(ostream &os, const CProjectFile &p)
{
    os<<p.strProjFileName<<'\n';
    os<<p.mFileDEM<<'\n';
    os<<p.mFileSlope<<'\n';
    os<<p.mFileAspect<<'\n';
    os<<p.mFileFuel<<'\n';
    os<<p.mWindSpeed<<'\n';
    os<<p.mWindDirection<<'\n';
    os<<p.m1hMoisture<<'\n';
    os<<p.m10hMoisture<<'\n';
    os<<p.m100hMoisture<<'\n';
    os<<p.mherbMoisture<<'\n';
    os<<p.mwoodMoisture<<'\n';
    return os;
}

istream & operator>>(istream &is, CProjectFile &p)
{
    is>>p.strProjFileName;
    is>>p.mFileDEM;
    is>>p.mFileSlope;
    is>>p.mFileAspect;
    is>>p.mFileFuel;
    is>>p.mWindSpeed;
    is>>p.mWindDirection;
    is>>p.m1hMoisture;
    is>>p.m10hMoisture;
    is>>p.m100hMoisture;
    is>>p.mherbMoisture;
    is>>p.mwoodMoisture;
    return is;

}
