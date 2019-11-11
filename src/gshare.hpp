#ifndef GSHARE_HPP
#define GSHARE_HPP

#include<vector>

#include"basicUnit.hpp"

using std::vector;

class GSharePredictor{

private:
const uint mask;
PatternEntry ghr;
vector<BitCounter> bht;

public:
GSharePredictor(const int bw);
bool getPrediction(const uint pc);
void updatePredictor(const uint pc, 
    const bool taken);

};

#endif