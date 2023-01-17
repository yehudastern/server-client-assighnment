#ifndef MANAGE_DATA_H
#define MANAGE_DATA_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "IDistance.hpp"
#include "DistanceFactory.hpp"

class ManageData {
private:
    vector<pair<vector<double>,string>> m_classified;
    vector<pair<vector<double>,string>> m_unclassified;
    DistanceFactory* m_distance;
    int m_k;
public:
    ManageData() : m_classified(), m_unclassified(), m_k(5){
        m_distance = new DistanceFactory("AUC");
    }
    ~ManageData();
};

ManageData::~ManageData() {
    delete m_distance;
}

#endif