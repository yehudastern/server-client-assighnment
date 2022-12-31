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
    vector<double> m_vec;
    IDistance* m_distance;
    int m_k;
    int m_flag;
    void initK(string num);
    void initDis(string disType);
    vector<pair<vector<double>, string>> getClsVecs(string fileName);

public:
    GetInput(string file);
    int getflag() const;
    void setInfo(string info);
    vector<pair<vector<double>,string>> getInputVec();
    IDistance* getDistance();
    int getK();
    vector<double> getVec();
    ~GetInput();
};

#endif
