#ifndef TWOBC_GSKEW_HPP
#define TWOBC_GSKEW_HPP

#include<vector>

#include"basicUnit.hpp"

using std::vector;

class TwoBCgskewPredictor{

private:
uint BIMindexBitsWidth;
uint BIMphtBitsWidth;
uint gBitsWidth;
uint metaBitsWidth;
uint BIMindexMask,BIMphtMask,gMask,metaMask;

vector<PatternEntry> BIMpht;
PatternEntry ghr;
vector<BitCounter> bbht,g1bht,g2bht,mbht;

private:
bool getBIMprediction(const uint& pc)const;
bool getG1prediction(const uint& pc)const;
bool getG2prediction(const uint& pc)const;
inline bool voter(const bool& BIMprediction,
    const bool& g1Prediction,
    const bool& g2Prediction)const;
bool getMetaSelection(const uint& pc)const;

void updateBIM(const uint& pc, const bool& taken);
void updateG1(const uint& pc, const bool& taken);
void updateG2(const uint& pc, const bool& taken);

public:
TwoBCgskewPredictor(const uint _BIMindexBitsWidth,
    const uint _BIMphtBitsWidth,
    const uint _gBitsWidth,
    const uint _metaBitsWidth);
TwoBCgskewPredictor(const uint maxBitsWidth);
TwoBCgskewPredictor();
bool getPrediction(const uint pc)const;
void updatePredictor(const uint pc, 
    const bool taken);

};

#endif