#ifndef MANAGE_DATA_H
#define MANAGE_DATA_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "IDistance.hpp"
#include "DistanceFactory.hpp"

/*
 * this class stores the data the different commands use.
 * it has the classified vector with the tags and the unclassified vector
 * without the tags, also it has the distance method and the k.
 * it lies in cli.
 */
class ManageData {
private:
    // saves the vector of the classified data
    vector<pair<vector<double>,string>> m_classified;
    // saves that of the unclassified
    vector<pair<vector<double>,string>> m_unclassified;
    // stores the distance calculator
    DistanceFactory* m_distance;
    // stores the k given
    int m_k;
    // stores the distance method and starts it as auc
    string m_disStr = string("AUC");
public:
    // starts k as 5 and distance factory as auc
    ManageData() : m_classified(), m_unclassified(), m_k(5){
        m_distance = new DistanceFactory("AUC");
    }
    // deletes m_ distance in the end
    ~ManageData() {
        delete m_distance;
    }
    // sets the unclassified vector
    void setUnclassified(vector<pair<vector<double>,string>> unclassified);
    // gets the vectors
    vector<pair<vector<double>,string>> getUnclassified();
    vector<pair<vector<double>,string>> getClassified();
    // sets the classified and the distance method string
    void setClassified(vector<pair<vector<double>,string>>);
    void setDisString(string);
    // returns the distance and the k
    string getDisString();
    int getK();
    // sets k
    void setK(int);
    // gets the distance factort
    DistanceFactory* getDistance();
    // sets the distance factory
    void setDistance(DistanceFactory*);
};

#endif