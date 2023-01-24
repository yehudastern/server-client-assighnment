#include "Knn.hpp"
#include "distances.hpp"

/*
 This code is an implementation of the K-Nearest Neighbors (KNN) algorithm.
 The KNN algorithm is a classification algorithm that takes in a labeled dataset
 and a new unlabeled data point and assigns a label to the new data point
 based on the labels of the nearest data points in the labeled dataset.
*/
Knn::Knn(vector<pair<vector<double>,string>> vector, int k, IDistance* distance) {
    //our data
    m_inputVec = vector;
    //k for labeled
    m_k = k;
    m_flag = 1;
    // for calculate distance between the vectors.
    m_distance = distance;
}

int Knn::getFlag() {
    return m_flag;
}

/*
 * takes in an input vector of doubles and returns a vector of pairs
 * containing the distances between the input vector and each vector in the labeled dataset,
 * as well as the corresponding label string.
 */
vector<pair<double,string>> Knn::getDisAndStr(const vector<double>& input){
    vector<pair<double,string>> vec;
    for(const auto& vector: m_inputVec) {
        // check the unclassified vector have a same size to the classified vector,  if not send a error massage
        if (vector.first.size() != input.size()) {
             m_flag = 0;
             break;
        }
        vec.emplace_back(m_distance->getDistance(vector.first, input),vector.second);
    }
    return vec;
}
/*
 takes in a vector of pairs with distance and string values and returns a vector of just the distance values.
*/
vector<double> Knn::getNoStrDis(const vector<pair<double,string>>& vec) {
    vector<double> vec1;
    for(const auto& v: vec) {
        vec1.push_back(v.first);
    }
    return vec1;
}
/*
 takes in a distance value k and a vector of pairs with distance and string values
 and returns a map with the labels as keys and the number of times each label appears in the input vector as values.
*/
map<string,int> Knn::createMap(double k, const vector<pair<double,string>>& vec) {
    map<string, int> tagMap;
    for(const auto& v: vec) {
        if(v.first <= k) {
            if (tagMap.count(v.second) > 0) {
                tagMap.at(v.second)++;
            } else {
                tagMap.insert(make_pair(v.second,1));
            }
        }
    }
    return tagMap;
}

/*
the getTag function uses the previously defined member functions
 to calculate the distances between the input vector and the vectors in the labeled dataset,
 select the k smallest distances, create a map of the labels for the vectors with those distances,
 and return the label that appears the most times in the map.
 This label is the predicted label for the input vector
*/
string Knn::getTag(const vector<double>& input) {
    vector<pair<double,string>> vec = getDisAndStr(input);
    if (m_flag == 0){
        return "-1";
    }
    vector<double> vec2 = getNoStrDis(vec);
    double k = select(vec2, m_k);
    map<string, int> tagMap = createMap(k, vec);
    int maxValue = 0;
    string tag;
    // Iterate over the map and update the maximum value and key if necessary.
    for (const auto& m : tagMap) {
        if (m.second > maxValue) {
            maxValue = m.second;
            tag = m.first;
        }
    }
    return tag;
}
