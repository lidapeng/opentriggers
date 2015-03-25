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
    vector<long> readInputRasterFeature();
};

#endif // CRASTERTRIGGERINPUT_H
