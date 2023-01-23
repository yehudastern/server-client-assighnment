#include "ManageData.h"

vector<pair<vector<double>,string>>ManageData::getClassified(){
    return m_classified;
}

void ManageData::setClassified(vector<pair<vector<double>,string>> classified) {
    m_classified = classified;
}
vector<pair<vector<double>,string>> ManageData::getUnclassified() {
    return m_unclassified;
}

void ManageData::setUnclassified(vector<pair<vector<double>,string>> unclassified) {
    m_unclassified = unclassified;
}

void ManageData::setDisString(string disStr) {
    m_disStr =  disStr;
}

string ManageData::getDisString(){
    return m_disStr;
}

int ManageData::getK(){
    return m_k;
}

void ManageData::setK(int k) {
    m_k = k;
}
DistanceFactory* ManageData::getDistance() {
    return m_distance;
}

void ManageData::setDistance(DistanceFactory* distance) {
    delete m_distance;
    m_distance = distance;
}