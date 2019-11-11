

#include"basicUnit.hpp"

BitCounter::BitCounter(const uint initValue, 
    const uint _bitsWidth):
    counter(initValue),
    bitsWidth(_bitsWidth),
    MSB(1<<(_bitsWidth-1)),
    mask((1<<_bitsWidth)-1)
{}

BitCounter::BitCounter(const uint initValue):
BitCounter(initValue,2)
{}

BitCounter::BitCounter():
BitCounter(1,2)
{}

bool BitCounter::getPrediction() const{
    return MSB&counter;
}

void BitCounter::updateLevel(const bool taken){
    counter+=(mask^counter)&&taken;
    counter-=counter&&!taken;
    counter&=mask;
}

PatternEntry::PatternEntry(const uchar bitsWidth):
pattern(0)
{
    mask=(1<<bitsWidth)-1;
}

uint PatternEntry::getPattern() const{
    return pattern&mask;
}

void PatternEntry::updatePattern(const bool taken){
    pattern=(pattern<<1)|taken;
}