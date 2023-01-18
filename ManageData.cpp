#include "ManageData.h"

ManageData::ManageData() : m_classified(), m_unclassified(), m_k(5){
    m_distance = new DistanceFactory("AUC");
}

ManageData::~ManageData() {
    delete m_distance;
}
