#ifndef CFIREBEHAVIOR_H
#define CFIREBEHAVIOR_H
#include "ctriggers.h"
#include <QtCore>
using namespace std;

class CFireBehavior: public QObject
{
   Q_OBJECT
public:
    CFireBehavior(CTriggers* projData);


private:
    CTriggers* mProj;

};

#endif // CFIREBEHAVIOR_H
