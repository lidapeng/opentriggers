#ifndef CUTILITIES_H
#define CUTILITIES_H
#include <iostream>
#include <string>
#include <QString>
using namespace std;

class CUtilities
{
public:
    CUtilities();
    static string QStringToString(QString& str);
    static QString StringToQstring(const string& str);
};

#endif // CUTILITIES_H
