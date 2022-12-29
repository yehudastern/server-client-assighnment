#include "distances.hpp"

/*
turned the distance methode into classes with 
the getdistance function.
 */

/*
  returns the roof of the sum -(v1i - v2i)^2 for every 0<i<n+1 in v1 and v2
*/
double euclideanDistance::getDistance(vector<double> v1, vector<double> v2) {
  int count = 0;
  double sum = 0;
  for (const double& i : v1) {
    // sums up q-p squared
    sum += (i - v2.at(count)) * (i - v2.at(count)); 
    count++;
  } // than returns the root of the sum
  return sqrt(sum);
}
/*
  returns the sum-|v1i - v2i| for every 0<i<n+1 in v1 and v2
*/
double manhatenDistance::getDistance(vector<double> v1, vector<double> v2) {
  int count = 0;
  double sum = 0;
  for (const double& i : v1) {
    // adds of the absolote substraction of the two numbers in the vectore at the same position
    sum += abs(i - v2.at(count)); 
    count++;
  }
  return sum;
}
/*
  returns the biggest absolute result of substraction
  of two nums in the same position on the two vectors
*/
double chebyshevDistance::getDistance(vector<double> v1, vector<double> v2) {
  double biggest = 0;
  int end = v1.size();
  for (int i = 0; i < end; i++) {
    double distance = abs(v1[i] - v2[i]);
    biggest = max(biggest, distance);
  }
  return biggest;
}
/*
  returns the sum - for every index it add to the same the absolote value
  of |v1i =v2i| / (|v1i| + |v2i|) unless v1i and v2i equals 0 in which cases it
  skips and leaves a message it did.
*/
double canberraDistance::getDistance(vector<double> v1, vector<double> v2) {
  int count = 0;
  double sum = 0;
  for (const double& i : v1) {
    double numarator = abs(i - v2.at(count)); // the numaratoc claculation
    double denominator = abs(i) + abs(v2.at(count)); // the denomination calculation
    if (denominator == 0) { // skipping as to not divide by zero
      cout << "ignoring a denominator of zero";
      continue;
    }
    sum += numarator / denominator;
    count++;  
  }
  return sum;
}
/*
  the minkowski Distance happens to be the same algo as the euclidian 
  distance formula for p = 2, so thats what it returns.
*/
double minkowskiDistance::getDistance(vector<double> v1, vector<double> v2) {
  int count = 0;
  double sum = 0;
  for (const double& i : v1) {
    // sums up q-p squared
    sum += (i - v2.at(count)) * (i - v2.at(count)); 
    count++;
  } // than returns the root of the sum
  return sqrt(sum);
}
