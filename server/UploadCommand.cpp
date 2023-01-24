#include "Command.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


UploadCommand::UploadCommand(ManageData* data, DefaultIO* dio) {
    m_description = "1. upload an unclassified csv data file";
    m_data = data;
    m_dio = dio;
}

int UploadCommand::getTrainData() {
    // start the vector
    vector<pair<vector<double>, string>> vecs;
    // if we get done, is done is true and we leave
    bool isDone = false;
    // used to see if we get invalid file input in the start to leave than
    bool start = true;
    // keeps reading and processing going until we get done
    while(true) {
        // if were done leaves
        if (isDone)
            break;
        // start reading lines
        string getLines = m_dio->read();
        string::size_type index = 0;
        // if we get invalid file input we leave
        if (start && (getLines.find("invalid file input", index) != string::npos)) {
            return 0;
        }// writes to fix the bad input issue
        m_dio->write("success");
        start = false;
        string line;
        std::istringstream ss(getLines);
        //goes over each line and process it into a vector
        while (getline(ss, line)) {
            // making a string stream in order to saparate the spaces
            index = 0;
            // if we get end we leave
            if (line.find("end", index) != string::npos) {
                isDone = true;
                break;
            }
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
            vecs.emplace_back(vec, tag);
        }
    }
    // sets the data for the other commands
    m_data->setClassified(vecs);
    return 1;
}

int UploadCommand::getTestData() {
    // start the vector
    vector<pair<vector<double>, string>> vecs;
    // if we get done, is done is true and we leave
    bool isDone = false;
    // used to see if we get invalid file input in the start to leave than
    bool start = true;
    // keeps reading and processing going until we get done
    while(true) {
        // if were done leaves
        if (isDone)
            break;
        // start reading lines
        string getLines = m_dio->read();
        string::size_type index = 0;
        // if we get invalid file input we leave
        if (start && (getLines.find("invalid file input", index) != string::npos)) {
            return 0;
        }// writes to fix the bad input issue
        m_dio->write("success");
        start = false;
        string line;
        std::istringstream ss(getLines);
        //goes over each line and process it into a vector
        while (getline(ss, line)) {
            // making a string stream in order to saparate the spaces
            index = 0;
            // if we get end we leave
            if (line.find("end", index) != string::npos) {
                isDone = true;
                break;
            }
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
    m_data->setUnclassified(vecs);
    return 1;
}

void UploadCommand::execute() {
    m_dio->write("Please upload your local train CSV file");
    if (!getTrainData()) {
        return;
    }
    m_dio->write("complete Upload.");
    m_dio->write("Please upload your local train CSV file");
    if (!getTestData()) {
        return;
    }
    m_dio->write("complete Upload.");
}