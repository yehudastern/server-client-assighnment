#include "../client/CommandClient.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>
std::mutex mtx;

UploadCommandClient::UploadCommandClient(DefaultIOCli* dio) {
    m_dio = dio;
}

AlgorithmSettingCommandClient::AlgorithmSettingCommandClient(DefaultIOCli* dio) {
    m_dio = dio;
}
    
ClassifyCommandClient::ClassifyCommandClient(DefaultIOCli* dio) {
    m_dio = dio;
}

DisplayCommandClient::DisplayCommandClient(DefaultIOCli* dio) {
    m_dio = dio;
}

DownloadCommandClient::DownloadCommandClient(DefaultIOCli* dio){
    m_dio = dio;
}

void UploadCommandClient::uploadCls(char* fileName) {
    std::unique_lock<std::mutex> lock(mtx);
    ifstream file(fileName);
    // while the file is open
    if (file.is_open()) {
        // will take each line from the stream
        string line;
        // while we have more lines to take
        while (getline(file, line)) {
            // replaces the commas with spaces
            replace(line.begin(), line.end(), ',', ' ');
            // making a string stream in order to saparate the spaces
            stringstream stream(line);
            // a vector of doubles
            //char *c = const_cast<char *>(line.c_str());
            m_dio->write(line);
        }
        lock.unlock();
    }
    string line = "end";
    //char *c = const_cast<char *>(line.c_str());
    m_dio->write(line);
    // close the file
    file.close();
}

int fileWorks(char* fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        file.close();
        return 1;
    } else {
        // exit the program
        cout << "Invalid input!" << endl;
        return 0;
    }
}

void UploadCommandClient::execute() {
    char s[2] = "1";
    m_dio->write(s);
    cout << m_dio->read() << endl;
    string fileName;
    cin >> fileName;
    char* c = const_cast<char *>(fileName.c_str());
    if (!fileWorks(c)) {
        string invalidMessage = "invalid file input";
        //char* invalidMess = const_cast<char *>(invalidMessage.c_str());
        m_dio->write(invalidMessage);
        return;
    }
    uploadCls(c);
    cout << m_dio->read() << endl;
    cout << m_dio->read() << endl;
    cin >> fileName;
    c = const_cast<char *>(fileName.c_str());
    if (!fileWorks(c)) {
        string invalidMessage = "invalid file input";
        char* invalidMess = const_cast<char *>(invalidMessage.c_str());
        m_dio->write(invalidMess);
        return;
    }
    uploadCls(c);
    cout << m_dio->read() << endl;
}


void AlgorithmSettingCommandClient::execute() {
    char s[2] = "2";
    m_dio->write(s);
    cout << m_dio->read() << endl;
    string input;
    cin.ignore();
    getline(cin, input);
    if (input.empty()) {
        m_dio->write(string("save the current parameters"));
    } else {
        m_dio->write(input);
    }
    string massege = m_dio->read();
    if(massege != "vaild input") {
        cout << massege << endl;
    }
}

void ClassifyCommandClient::execute() {
    char s[2] = "3";
    m_dio->write(s);
    cout << m_dio->read() << endl;
}

void DisplayCommandClient::execute() {
    char s[2] = "4";
    m_dio->write(s);
    int numLine = 1;
    while (true){
        string s = m_dio->read();
        if(s.find("please upload data", 0) != string::npos || s.find("please classify the data", 0) != string::npos) {
            cout << s << endl;
            return;
        }
        if (s.find("Done", 0) != string::npos) {
            break;
        }
        cout << to_string(numLine) + "      " + s << endl;
        numLine++;
    }
    cout << "Done." << endl;
}

void DownloadCommandClient::execute() {
    char s[2] = "5";
    m_dio->write(s);
    std::ofstream file;
    string dataFile;
    cin.ignore();
    getline(cin, dataFile);
    string tagForFile;
    while (true) {
        if(tagForFile.find("please upload data", 0) != string::npos) {  
            cout << "please upload data" << endl;
            return;
        }
        if (tagForFile.find("please classify the data", 0) != string::npos) {
            cout << "please classify the data" << endl;
            return;
        }
        tagForFile += m_dio->read() + " ";
        if(tagForFile.find("Done", 0) != string::npos) {
            break;
        }
    }
    file.open(dataFile + "/Labeling.txt");
    if (!file.is_open()) {
        cout << "invalid pass" << endl;
        return;
    }
    file.close();
    thread thread(&DownloadCommandClient::writeToFile, this, dataFile + string("/Labeling.txt"), tagForFile);
    thread.detach();     
}

void DownloadCommandClient::writeToFile(const std::string& filePass, const std::string& tagForFile) {
    std::ofstream file;
    unique_lock<std::mutex> lock(mtx);
    file.open(filePass);
    int numLine = 1;
    string tagLine;
    stringstream line(tagForFile);
    while (line >> tagLine) { 
        if(tagLine.find("Done", 0) != string::npos) {
            break;
        }
        file << to_string(numLine) + "      "  + tagLine << endl;
        numLine++;
    }
    file.close();
    lock.unlock();
}