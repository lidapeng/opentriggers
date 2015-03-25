#ifndef CRASTERTRIGGERINPUT_H
#define CRASTERTRIGGERINPUT_H
#include "crasterdataset.h"
#include <vector>
using namespace std;

// A class to read input geographic feature for trigger modeling
class CRasterTriggerInput : public CRasterDataset
{
public:
    CRasterTriggerInput();
    CRasterTriggerInput(string strFile);
    vector<long> getInputRasterFeature();
};

#endif // CRASTERTRIGGERINPUT_H
