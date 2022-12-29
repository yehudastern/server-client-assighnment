#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Knn.hpp"
#include "DistanceFactory.hpp"
#include "GetInput.hpp"
using namespace std;

GetInput::GetInput(string file, string data){
    m_flag = 1;
    m_inputVec = getClsVecs(file);
    
}
GetInput::~GetInput() {
}

void GetInput::testDis(string disType) {
    if ( !((disType == "AUC") || (disType == "MAN") || (disType == "CHB")|| (disType == "CAN" )|| (disType == "MIN"))) {
        m_flag =0;
    }
}
void GetInput::takeVecKAndDis(string info) {
    string line;
    // making a string stream in order to saparate the spaces
    stringstream stream(line);
    // a vector of doubles
    vector<double> vec;
    // a string for each word in the line
    string y = "";
    string disType;
    string k;
    // a double to put the numbers in
    double x;
    int stay = 1;
    int moreDoubles = 1;
    // while we have more words to put in y string
    while (stay && stream >> y) {
        // we use an istring stream to convert the word to double
        istringstream iss(y);
        // if the converstion was made we put the double in the vector
        if (moreDoubles && iss >> x) {
            vec.push_back(x);
        }
        // else we have a string and we break
        else {
        // adds a space if theres more strings in the end
            if (!stream.eof())
                disType = y;
            // else adds with no space
            else
                k = y;
                stay = 0;
        }
        if (!k.empty() && !disType.empty()) {
            testK(k);
            testDis(disType);
            m_k = stoi(k);
            m_distance = new DistanceFactory(disType);
             
        } else {
            m_flag = 0;
        }
    }
}



vector<pair<vector<double>, string>> GetInput::getClsVecs(string fileName){
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
        m_inputVec = vecs;
    }
    // if there was a mistake and the file isnt open
    else {
        m_flag = 0;
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
void GetInput::testK(string num){
    for (char c : num) {
        if(!isdigit(c)){
            m_flag = 0;
        }
    }
    if(m_inputVec.size() < stoi(num)){
        m_flag = 0;
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
        if (failed) {
            delete ds;
            exit(1);
        }
        string tag = myKnn.getTag(inputVec);
        cout << tag << endl;
    }
}