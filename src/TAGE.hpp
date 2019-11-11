#ifndef TAGE_HPP
#define TAGE_HPP

#include<vector>

#include"basicUnit.hpp"

using std::vector;

class _TagEntry{

private:
    BitCounter counter;
    uint tag;
    uint usefulBits;

public:
    _TagEntry(const uint counterBitWidth,
        const uint icounter,
        const uint itag,
        const uint iusefulBits);
    _TagEntry(const uint icounter,
        const uint itag,
        const uint iusefulBits);

};

class _CompressedHistoryEntry{

private:
    uint historyBitsWidth;
    uint targetBitsWidth;
    uint historySize;
    uint targetSize;
    uint historyMask;
    uint targetMask;
    uint history;
    

public:
    _CompressedHistoryEntry(const uint _historyBitsWidth,
        const uint _targetBitsWidth,
        const uint _history);
    _CompressedHistoryEntry(const uint _historyBitsWidth,
        const uint _targetBitsWidth);
    
    void updateHistory(const PatternEntry& ghr);

};

class TAGE_Predictor{

private:

static const uint basePredictorSize=1024;
static const uint numTagTables=4;
static const uint tagPredictorSize=1024;


vector<BitCounter> basePredictors;
vector<_TagEntry> tagPredictors;
uint historyMasks[4];

public:

TAGE_Predictor();
bool getPrediction(const uint pc);
void updatePredictor(const uint pc,
    const bool taken);

};

#endif