


#include"tournament.hpp"

TournamentPredictor::TournamentPredictor(const uint ghistoryBits,
    const uint pcIndexBits,
    const uint lhistoryBits):
ghistoryMask((1<<ghistoryBits)-1),
pcIndexMask((1<<pcIndexBits)-1),
lhistoryMask((1<<lhistoryBits)-1),
ghr(ghistoryBits),
gbht(1<<ghistoryBits),
lbht(1<<lhistoryBits),
selectors(1<<ghistoryBits,BitCounter(2))
{
    lpht.resize(1<<pcIndexBits,PatternEntry(lhistoryBits));
}

bool TournamentPredictor::getLocalPrediction(const uint& pc){
    uint lphtIndex=pc&pcIndexMask;
    return lbht[lpht[lphtIndex].getPattern()].getPrediction();
}

bool TournamentPredictor::getGlobalPrediction(const uint& pc){
    uint index=ghr.getPattern();
    return gbht[index].getPrediction();
}

bool TournamentPredictor::getFinalPrediction(const uint& pc,
    const bool& globalPrediction,
    const bool& localPrediction){
    const uint selectorIndex=ghr.getPattern();
    const bool selection=selectors[selectorIndex].getPrediction();
    return (selection&globalPrediction)|
        ((!selection)&localPrediction);
}

bool TournamentPredictor::getPrediction(const uint pc){
    return getFinalPrediction(pc,
        getGlobalPrediction(pc),
        getLocalPrediction(pc));
}

void TournamentPredictor::updatePredictor(const uint pc, 
    const bool taken){

    const uint lphtIndex=pc&pcIndexMask;
    const uint gbhtIndex=ghr.getPattern();
    const uint selectorIndex=ghr.getPattern();
    const bool isGlobalPredictionCorrect=!(taken^getGlobalPrediction(pc));
    const bool isLocalPredictionCorrect=!(taken^getLocalPrediction(pc));

    gbht[gbhtIndex].updateLevel(taken);
    ghr.updatePattern(taken);
    lbht[lpht[lphtIndex].getPattern()].updateLevel(taken);
    lpht[lphtIndex].updatePattern(taken);
    if(isGlobalPredictionCorrect^isLocalPredictionCorrect){
        selectors[selectorIndex].updateLevel(isGlobalPredictionCorrect);
    }
    
}