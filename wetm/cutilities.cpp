#include "cutilities.h"

CUtilities::CUtilities()
{
}

string CUtilities::QStringToString(QString &str)
{
    std::string strCPP = str.toLocal8Bit().constData();
    return strCPP;
}

QString CUtilities::StringToQstring(const string &str)
{
    return QString::fromStdString(str);
}
