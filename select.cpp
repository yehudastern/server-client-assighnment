#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


/*
This code is an implementation of the select function,
which is used to select the kth smallest element from a given vector of values.
the function do it in O(n) runtime.
*/

/*
 Standard partition process of QuickSort() It considers the first element as pivot
 and moves all smaller element to left of it and greater elements to right.
*/
int partition(vector<double> &vec, double pivot) {
    int i;
    int j = 0;
    for (i = 1 ; i < vec.size(); i++) {
        if (vec.at(i) <= pivot) {
            j++;
            swap(vec.at(i), vec.at(j));
        }
    }
    swap(vec.at(0), vec.at(j));
    return j;
}

/*
The findPivot function is used to find the pivot value for the partition function.
This function recursively divides the input vector into groups of 5 and finds the median of each group.
The medians of all the groups are then used to find the final pivot value.
*/
double findPivot(vector<double> vector) {
    unsigned long long vecSize = vector.size();
    if(vecSize <= 5){
        sort(vector.begin(), vector.end());
        return vector.at(vecSize/2);
    }
    std::vector<double> vec2;
    std::vector<double> vec3;
    int i;
    for(i = 0; i < vecSize; i++) {
        if(i%5 == 0 && i != 0){
            sort(vec2.begin(),vec2.end());
            vec3.push_back(vec2.at(ceil(vec2.size()/2)));
            vec2.clear();
        }
        vec2.push_back(vector.at(i));
    }
    return findPivot(vec3);
}
/*
The select function then uses the partition and findPivot functions
 to find the kth smallest element in the input vector.
 It first finds the pivot value for the input vector and partitions the vector based on the pivot value.
 If the pivot value is the kth smallest element, it is returned.
 Otherwise, the function recursively calls itself on the appropriate portion of the vector
 depending on whether the pivot value is smaller or larger than the kth smallest element.
*/
double select(vector<double> vec, int k) {
    vector<double> copy(std::move(vec));
    auto median = findPivot(copy);
    auto y = find(copy.begin(), copy.end(), median);
    rotate(copy.begin(), y, copy.end());
    int x = partition(copy,median);
    if(x + 1 == k) {
        return copy.at(x);
    } else if (x + 1 < k){
        copy.erase(copy.begin(), copy.begin() + x);
        return select(copy,k - x);
    } else {
        copy.erase(copy.begin() + x, copy.end());
        return select(copy,k);
    }
}
