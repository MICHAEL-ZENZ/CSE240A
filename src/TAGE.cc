

#include"TAGE.hpp"

_TagEntry::_TagEntry(const uint counterBitWidth,
    const uint icounter,
    const uint itag,
    const uint iusefulBits):
    counter(icounter,counterBitWidth),
    tag(itag),
    usefulBits(iusefulBits)
{}

_TagEntry::_TagEntry(const uint icounter,
    const uint itag,
    const uint iusefulBits):
    _TagEntry(2,icounter,itag,iusefulBits)
{}

_CompressedHistoryEntry::_CompressedHistoryEntry(const uint _historyBitsWidth,
        const uint _targetBitsWidth,
        const uint _history):
    historyBitsWidth(_historyBitsWidth),
    targetBitsWidth(_targetBitsWidth),
    historySize(1<<_historyBitsWidth),
    targetSize(1<<_targetBitsWidth),
    historyMask((1<<_historyBitsWidth)-1),
    targetMask((1<<_targetBitsWidth)-1),
    history(_history)
{}

_CompressedHistoryEntry::_CompressedHistoryEntry(const uint _historyBitsWidth,
        const uint _targetBitsWidth):
    _CompressedHistoryEntry(_historyBitsWidth,_targetBitsWidth,0)
{}

void _CompressedHistoryEntry::updateHistory(const PatternEntry& ghr){
    uint globalHistoryResized=ghr.getPattern()&historyMask;
    uint compressedHistory=0;
    while(globalHistoryResized){
        compressedHistory^=(globalHistoryResized&targetMask);
        globalHistoryResized>>=targetBitsWidth;
    }
}

TAGE_Predictor::TAGE_Predictor():
basePredictors(basePredictorSize),
tagPredictors(tagPredictorSize,_TagEntry(0,0,0))
{
    historyMasks[0]=130;
    historyMasks[1]=44;
    historyMasks[2]=15;
    historyMasks[3]=5;


}

