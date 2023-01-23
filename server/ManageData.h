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
    string m_disStr = string("AUC");
public:
    ManageData() : m_classified(), m_unclassified(), m_k(5){
        m_distance = new DistanceFactory("AUC");
    }
    ~ManageData() {
    delete m_distance;
    }
    void setUnclassified(vector<pair<vector<double>,string>> unclassified);
    vector<pair<vector<double>,string>> getUnclassified();
    vector<pair<vector<double>,string>> getClassified();
    void setClassified(vector<pair<vector<double>,string>>);
    void setDisString(string);
    string getDisString();
    int getK();
    void setK(int);
    DistanceFactory* getDistance();
    void setDistance(DistanceFactory*);
};

#endif