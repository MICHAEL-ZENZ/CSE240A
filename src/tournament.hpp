#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include<vector>

#include"basicUnit.hpp"

using std::vector;

class TournamentPredictor{

private:

const uint ghistoryMask;
const uint pcIndexMask;
const uint lhistoryMask;

PatternEntry ghr;
vector<BitCounter> gbht;
vector<PatternEntry> lpht;
vector<BitCounter> lbht;
vector<BitCounter> selectors;

private:

bool getLocalPrediction(const uint& pc);
bool getGlobalPrediction(const uint& pc);
bool getFinalPrediction(const uint& pc,
    const bool& globalPrediction,
    const bool& localPrediction);

public:

TournamentPredictor(const uint ghistoryBits,
    const uint pcIndexBits,
    const uint lhistoryBits);
bool getPrediction(const uint pc);
void updatePredictor(const uint pc, 
    const bool taken);

};

#endif