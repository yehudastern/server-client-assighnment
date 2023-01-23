#ifndef DISTANCE_INTERFACE_HPP
#define DISTANCE_INTERFACE_HPP
#include <iostream>
#include <vector>

using namespace std;
// this is an interface for a distance class
class IDistance {
    // gets the distance from two vectors
    public:
        virtual double getDistance(vector<double> v1, vector<double> v2) = 0;
        // destructor
        virtual ~IDistance() {};
};

#endif