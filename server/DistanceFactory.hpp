#ifndef DISTANCE_FACTORY_HPP
#define DISTANCE_FACTORY_HPP

#include <string>
#include <iostream>
#include <vector>
#include "distances.hpp"
#include "IDistance.hpp"
#include <memory>

using namespace std;
// uses a certain distance method according to the string provided

class DistanceFactory : public IDistance {
    private:
        IDistance* m_distance;
    public:
        double getDistance(vector<double> v1, vector<double> v2) override;
        // constructor that sets m_distance by string
        DistanceFactory(const std::string& distanceName);
        void setDistance(string);
        // destructor
        ~DistanceFactory() override;
};

#endif