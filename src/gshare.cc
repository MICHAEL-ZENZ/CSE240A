


#include"gshare.hpp"


GSharePredictor::GSharePredictor(const int bitsWidth):
mask((1<<bitsWidth)-1),
ghr(bitsWidth),
bht(1<<bitsWidth)
{}

bool GSharePredictor::getPrediction(const uint pc){
    uint index=(pc&mask)^ghr.getPattern();
    return bht[index].getPrediction();
}

void GSharePredictor::updatePredictor(const uint pc,
    const bool taken){
    uint index=(pc&mask)^ghr.getPattern();
    bht[index].updateLevel(taken);
    ghr.updatePattern(taken);
}