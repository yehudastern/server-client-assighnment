#ifndef GET_INPUT_HPP
#define GET_INPUT_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "IDistance.hpp"

class GetInput{
private:
    vector<pair<vector<double>,string>> m_inputVec;
    IDistance* m_distance;
    int m_k;
    int m_flag;
    void testK(string num);
    void testDis(string disType);
    vector<pair<vector<double>, string>> getClsVecs(string fileName);
    void takeVecKAndDis(string info);
public:
    GetInput(string file, string data);
    int getflag();
    vector<pair<vector<double>,string>> getInputVec();
    IDistance* getDistance();
    int getK();
    ~GetInput();
};

#endif
