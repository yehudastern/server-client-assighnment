#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "DistanceFactory.hpp"
#include "GetInput.hpp"
using namespace std;

GetInput::GetInput(string file){
    m_flag = 1;
    m_inputVec = getClsVecs(file);
}

GetInput::~GetInput() {
    delete m_distance;
}

int GetInput::getflag() const{
    return m_flag;
}
vector<pair<vector<double>,string>> GetInput::getInputVec(){
    return m_inputVec;
}

IDistance* GetInput::getDistance() {
    return m_distance;
}

int GetInput::getK() {
    return m_k;
}

vector<double> GetInput::getVec() {
    return m_vec;
}


void GetInput::initDis(string disType) {
    if (!((disType == "AUC") || (disType == "MAN") || (disType == "CHB")|| (disType == "CAN" )|| (disType == "MIN"))) {
        m_flag = 0;
    } else {
        m_distance = new DistanceFactory(disType);
    }
}

void GetInput::setInfo (string info) {
    string line = std::move(info);
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
    int moreDoubles = 1;
    // while we have more words to put in y string
    while (stream >> y) {
        // we use an istring stream to convert the word to double
        istringstream iss(y);
        // if the converstion was made we put the double in the vector
        if (moreDoubles && iss >> x) {
            vec.push_back(x);
        }
        // else we have a string and we break
        else {
            moreDoubles = 0;
            // adds a space if theres more strings in the end
            if (!stream.eof())
                disType = y;
            // else adds with no space
            else {
                k = y;
                break;
            }
        }
    }
    //cout << "distance: " << disType << " k: " << k << endl;
    if (!k.empty() && !disType.empty()) {
        initK(k);
        initDis(disType);
    } else {
        m_flag = 0;
    }
//    for (double d: vec) {
//        //cout << d << " ";
//    }
//    //cout << endl;
    m_vec = vec;
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
void GetInput::initK(string num) {
    for (char c : num) {
        if(!isdigit(c)){
            m_flag = 0;
        }
    }
    if(m_inputVec.size() < stoi(num) || stoi(num) <= 0){
        m_flag = 0;
    }
    m_k = stoi(num);
}
