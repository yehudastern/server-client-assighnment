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
    vector<pair<vector<double>, string>> vecs;
    bool isDone = false;
    bool start = true;
    // Opening the file in read only mode
    // while the file is open
    while(true) {
        if (isDone)
            break;
        string getLines = m_dio->read();
        string::size_type index = 0;
        if (start && (getLines.find("invalid file input", index) != string::npos)) {
            return 0;
        }
        m_dio->write("success");
        start = false;
        string line;
        std::istringstream ss(getLines);
        while (getline(ss, line)) {
            // making a string stream in order to saparate the spaces
            index = 0;
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
    m_data->setClassified(vecs);
    return 1;
}

int UploadCommand::getTestData() {
    vector<pair<vector<double>, string>> vecs;
    bool isDone = false;
    bool start = true;
    // Opening the file in read only mode
    // while the file is open
    while(true) {
        if (isDone)
            break;
        string getLines = m_dio->read();
        string::size_type index = 0;
        if (start && (getLines.find("invalid file input", index) != string::npos)) {
            cout << "invalid file input" << endl;
            return 0;
        }
        m_dio->write("success");
        start = false;
        string line;
        std::istringstream ss(getLines);
        while (getline(ss, line)) {
            // making a string stream in order to saparate the spaces
            index = 0;
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
            if (vec.size() != 16) {
                for (double d: vec) {
                    cout << d << " ";
                }
                cout << endl;
                cout << line << endl;
            }
            // we take the double vector and the string in the end make a tuple from them and push them
            vecs.push_back(make_pair(vec, tag));
        }
    }
    // int i =1;
    // for (auto &v: vecs) {
    //     cout << i;
    //     i++;
    //     for(auto &ve: v.first) {
    //             cout << "    " << ve << " ";
    //     }
    //     cout << endl;
    // }
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