#ifndef BASIC_UNIT_HPP
#define BASIC_UNIT_HPP

typedef unsigned char uchar;
typedef unsigned int uint;

class BitCounter{
private:
    uint counter;
    uint bitsWidth;
    uint MSB;
    uint mask;
public:
    BitCounter();
    BitCounter(const uint initValue);
    BitCounter(const uint initValue, const uint _bitsWidth);
    bool getPrediction() const;
    void updateLevel(const bool taken);
};

class PatternEntry{
private:
uint mask;
uint pattern;

public:
PatternEntry(const uchar bitsWidth);
uint getPattern() const;
void updatePattern(const bool taken);

};

#endif