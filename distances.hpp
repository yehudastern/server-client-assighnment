#ifndef distances_HPP
#define distances_HPP
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "IDistance.hpp"

// all the distance classes, can be put in knn
using namespace std;
class euclideanDistance: public IDistance {
    public:
        double getDistance (vector<double> v1, vector<double> v2) override;
    // destructor
};
class manhatenDistance: public IDistance {
    public:
        double getDistance(vector<double> v1, vector<double> v2) override;
    // destructor
};
class chebyshevDistance: public IDistance {
    public:
        double getDistance(vector<double> v1, vector<double> v2) override;
    // destructor
};
class canberraDistance: public IDistance {
    public:
        double getDistance(vector<double> v1, vector<double> v2) override;
    // destructor
};
class minkowskiDistance: public IDistance {
    public:
        double getDistance(vector<double> v1, vector<double> v2) override;
    // destructor
};

#endif