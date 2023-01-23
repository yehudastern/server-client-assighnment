#include "DistanceFactory.hpp"
#include "distances.hpp"


DistanceFactory::DistanceFactory(const std::string& distanceName) {
    // we pick the distance embedded class accodrding to the provided string.
    if (distanceName == "AUC") 
        m_distance = new euclideanDistance();
    else if (distanceName == "MAN") 
        m_distance = new manhatenDistance();
    else if (distanceName == "CHB") 
        m_distance = new chebyshevDistance();
    else if (distanceName == "CAN") 
        m_distance = new canberraDistance();
    else if (distanceName == "MIN") 
        m_distance = new minkowskiDistance();
        // if the string is wrong exits
    else {
        std::cout << "distnace name error, change it" << std::endl;
        exit(1);
    }
}// using the distance methode of the embedded class
double DistanceFactory::getDistance(vector<double> v1, vector<double> v2) {
    return m_distance->getDistance(v1, v2);
} // destructor
DistanceFactory::~DistanceFactory() {
    delete m_distance;
}

void DistanceFactory::setDistance(string distanceName) {
    delete m_distance;
    // we pick the distance embedded class accodrding to the provided string.
    if (distanceName == "AUC") 
        m_distance = new euclideanDistance();
    else if (distanceName == "MAN") 
        m_distance = new manhatenDistance();
    else if (distanceName == "CHB") 
        m_distance = new chebyshevDistance();
    else if (distanceName == "CAN") 
        m_distance = new canberraDistance();
    else if (distanceName == "MIN") 
        m_distance = new minkowskiDistance();
        // if the string is wrong exits
    else {
        std::cout << "test distance failed" << std::endl;
        exit(1);
    }
}