

#include"2bc-gskew.hpp"

TwoBCgskewPredictor::TwoBCgskewPredictor(const uint _BIMindexBitsWidth,
    const uint _BIMphtBitsWidth,
    const uint _gBitsWidth,
    const uint _metaBitsWidth):
    BIMindexBitsWidth(_BIMindexBitsWidth),
    BIMphtBitsWidth(_BIMphtBitsWidth),
    gBitsWidth(_gBitsWidth),
    metaBitsWidth(_metaBitsWidth),
    BIMindexMask((1<<_BIMindexBitsWidth)-1),
    BIMphtMask((1<<_BIMphtBitsWidth)-1),
    gMask((1<<_gBitsWidth)-1),
    metaMask((1<<metaBitsWidth)-1),
    BIMpht(1<<_BIMindexBitsWidth,PatternEntry(_BIMphtBitsWidth)),
    ghr(_gBitsWidth),
    bbht(1<<_BIMphtBitsWidth),
    g1bht(1<<_gBitsWidth),
    g2bht(1<<_gBitsWidth),
    mbht(1<<_metaBitsWidth,BitCounter(2))
{}

TwoBCgskewPredictor::TwoBCgskewPredictor(const uint maxBitsWidth):
TwoBCgskewPredictor(maxBitsWidth-7,
maxBitsWidth-4,
maxBitsWidth-3,
maxBitsWidth-3)
{}

TwoBCgskewPredictor::TwoBCgskewPredictor():
TwoBCgskewPredictor(16)
{}

bool TwoBCgskewPredictor::getBIMprediction(const uint& pc)const{
    uint BIMindex=pc&BIMindexMask;
    return bbht[BIMpht[BIMindex].getPattern()].getPrediction();
}

bool TwoBCgskewPredictor::getG1prediction(const uint& pc)const{
    uint g1Index=(pc&gMask)^ghr.getPattern();
    return g1bht[g1Index].getPrediction();
}

bool TwoBCgskewPredictor::getG2prediction(const uint& pc)const{
    uint g2Index=(pc+ghr.getPattern())&gMask;
    return g2bht[g2Index].getPrediction();
}

inline bool TwoBCgskewPredictor::voter(const bool& BIMprediction,
    const bool& g1Prediction,
    const bool& g2Prediction)const{
    return (BIMprediction+g1Prediction+g2Prediction)>1;
}

bool TwoBCgskewPredictor::getMetaSelection(const uint& pc)const{
    uint metaIndex=ghr.getPattern();
    return mbht[metaIndex].getPrediction();
}

void TwoBCgskewPredictor::updateBIM(const uint& pc, const bool& taken){
    uint BIMindex=pc&BIMindexMask;
    bbht[BIMpht[BIMindex].getPattern()].updateLevel(taken);
    BIMpht[BIMindex].updatePattern(taken);
}

void TwoBCgskewPredictor::updateG1(const uint& pc, const bool& taken){
    uint g1Index=(pc&gMask)^ghr.getPattern();
    g1bht[g1Index].updateLevel(taken);
}

void TwoBCgskewPredictor::updateG2(const uint& pc, const bool& taken){
    uint g2Index=(pc+ghr.getPattern())&gMask;
    g2bht[g2Index].updateLevel(taken);
}

bool TwoBCgskewPredictor::getPrediction(const uint pc)const{
    bool BIMprediction=getBIMprediction(pc);
    bool metaSelection=getMetaSelection(pc);
    return (BIMprediction&!metaSelection)|
        (voter(BIMprediction,getG1prediction(pc),getG2prediction(pc))&metaSelection);
}

void TwoBCgskewPredictor::updatePredictor(const uint pc, 
    const bool taken){
    bool BIMprediction=getBIMprediction(pc);
    bool skewPrediction=voter(BIMprediction,getG1prediction(pc),getG2prediction(pc));
    bool isBIMpredictionCorrect=!(taken^BIMprediction);
    bool isSkewPredictionCorrect=!(taken^skewPrediction);
    uint metaIndex=ghr.getPattern();

    updateBIM(pc,taken);
    updateG1(pc,taken);
    updateG2(pc,taken);
    ghr.updatePattern(taken);
    if(isBIMpredictionCorrect^isSkewPredictionCorrect){
        mbht[metaIndex].updateLevel(isSkewPredictionCorrect);
    }
}