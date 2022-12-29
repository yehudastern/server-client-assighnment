#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Knn.hpp"
#include "DistanceFactory.hpp"


using namespace std;

/*
This function get vector from the user and check if the vector is valid.
The return value is the valid vector.
The function throw error and exit using failed if in input has "..", and if there is no number in the vector.
If characters are inserted, the vector will contain all the valid values until the character is inserted.
*/
vector<double> getInput(int* failed) {
    double x = 0;
    vector<double> v;
    string line;
    // get line from the user.
    getline(cin, line);
    // check if ".." are insert and exits using failed if so.
    if (line.find("..") != string::npos) {
        cout << "the input is not valid, because '..' was inserted!" << endl;
        *failed = 1;
    }
    // use in "istringstream" method to get only number.
    istringstream stream(line);
    // Go through all the input and insert only numbers into the vector,
    // In case we get an invalid value the loop will stop.
    while (stream >> x) {
        v.push_back(x);
    }
    // If no valid value is entered the program will exit using failed
    if(v.empty()) {
        cout << "please insert numbers correctly, try run it again!" << endl;
        *failed = 1;
    }
    return v;
}

vector<pair<vector<double>, string>> getClsVecs(string fileName){
    vector<pair<vector<double>, string>> vecs;
    // Opening the file in read only mode
    ifstream file(fileName);
    // while the file is open
    if (file.is_open()) {
        // will take each line from the stream
        string line;
        // while we have more lines to tak
        while (getline(file, line)) {
            // replaces the commas with spaces
            replace(line.begin(), line.end(), ',', ' ');
            // making a string stream in order to saparate the spaces
            stringstream stream(line);
            // a vector of doubles
            vector<double> vec;
            // a string for each word in the line
            string y = "";
            string tag;
            // a double to put the numbers in
            double x;
            // while we have more words to put in y string
            int stillNums = 1;
            while (stillNums && stream >> y) {
                // we use an istring stream to convert the word to double
                istringstream iss(y);
                // if the converstion was made we put the double in the vector
                if (iss >> x) {
                    vec.push_back(x);
                }
                    // else we have a string and we break
                else {
                    // adds a space if theres more strings in the end
                    if (!stream.eof())
                        tag += y + " ";
                    // else adds with no space
                    else
                        tag += y;
                }
            }
            // we take the double vector and the string in the end make a tuple from them and push them
            vecs.push_back(make_pair(vec, tag));
        }
    }
        // if there was a mistake and the file isnt open
    else {
        cout << "wrong file name!" << endl;
        exit(1);
    }
    // close the file
    file.close();
    return vecs;
}
/*
 This function tests whether a given string consists of only digits.
 If the string contains any non-digit characters,
 the function prints an error message and exits the program.
*/
void testK(string num){
    for (char c : num) {
        if(!isdigit(c)){
            cout << "the k is not valid!" << endl;
            exit(1);
        }
    }
}

/*
The program takes in three command line arguments:
 a value for k (the number of nearest neighbors to consider), a file containing the labeled training data,
 and a string indicating the distance metric to use.
*/
int main(int argc, char** argv) {
    // checks the number of command line arguments and validates the k value.
    if (argc != 4){
        cout << "insert currect input!" <<endl;
    }
    testK(argv[1]);
    int k = atoi(argv[1]);
    // reads the labeled training data from the input file
    vector<pair<vector<double>, string>> vecs = getClsVecs(argv[2]);
    // creates a KNN classifier using the specified distance metric.
    IDistance* ds = new DistanceFactory(argv[3]);
    Knn myKnn = Knn(vecs, k, ds);
    //enters an infinite loop to continuously read input vectors from the user,
    // classify them using the KNN classifier,
    // and print the predicted class label to the console.
    while (true) {
        int failed = 0;
        vector<double> inputVec = getInput(&failed);
        if (failed) {
            delete ds;
            exit(1);
        }
        string tag = myKnn.getTag(inputVec);
        cout << tag << endl;
    }
}