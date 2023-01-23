#ifndef KNN_HPP
#define KNN_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "select.hpp"
#include "IDistance.hpp"

using namespace std;
class Knn {
private:
    vector<pair<vector<double>,string>> m_inputVec;
    IDistance* m_distance;
    int m_k;
    int m_flag;
    vector<double> getNoStrDis(const vector<pair<double,string>>&);
    vector<pair<double,string>> getDisAndStr(const vector<double>&);
    map<string,int> createMap(double, const vector<pair<double,string>>&);
public:
    int getFlag();
    Knn(vector<pair<vector<double>,string>>, int, IDistance*);
    string getTag(const vector<double>&);
};



#endif //KNN_HPP