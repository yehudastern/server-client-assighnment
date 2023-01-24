#include "../client/CommandClient.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>

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
            m_dio->write(line);
            m_dio->read();
        }
        file.close();
    }
    string line = "end";
    m_dio->write(line);
}

int fileWorks(char* fileName) {
    ifstream file(fileName);
    // if file is open the path is legal
    if (file.is_open()) {
        file.close();
        return 1;
    } else {
        // print error massage
        cout << "Invalid input!" << endl;
        return 0;
    }
}

void UploadCommandClient::execute() {
    // oprate the server
    char s[2] = "1";
    m_dio->write(s);
    // print a massage from the server for upload data
    cout << m_dio->read() << endl;
    string fileName;
    // get path
    cin >> fileName;
    char* c = const_cast<char *>(fileName.c_str());
    // check the path
    if (!fileWorks(c)) {
        string invalidMessage = "invalid file input";
        // send error massagae to the server
        m_dio->write(invalidMessage);
        return;
    }
    // send the classified file to the server
    uploadCls(c);
    // get success massege from thr server
    string str = m_dio->read();
    // print a server massgae for upload unclassified data
    cout << m_dio->read() << endl;
    cout << m_dio->read() << endl;
    // get unclassified file path
    cin >> fileName;
    c = const_cast<char *>(fileName.c_str());
    // check the path
    if (!fileWorks(c)) {
        string invalidMessage = "invalid file input";
        m_dio->write(invalidMessage);
        return;
    }
    // send the unclassified data to the server
    uploadCls(c);
    // print seccess massage from the server
    str = m_dio->read();
    cout << m_dio->read() << endl;
}

void AlgorithmSettingCommandClient::execute() {
    // operate the setting command in server
    char s[2] = "2";
    m_dio->write(s);
    // print a massage form the server for insert k and distance
    cout << m_dio->read() << endl;
    // get k and dis from the user
    string input;
    cin.ignore();
    getline(cin, input);
    // check if the input is empty
    if (input.empty()) {
        m_dio->write(string("save the current parameters"));
    } else {
        // send input to server
        m_dio->write(input);
    }
    // get massege from the server to vaildate the input
    string massege = m_dio->read();
    // check if the server send "invalid value for K" or "invalid value for metric",  and print a aprropriate massage
    if(massege.find("invalid value for K", 0) != string::npos) {
        cout << "invalid value for K" << endl;
        if(massege.find("invalid value for metric", 0) != string::npos) {
            cout << "invalid value for metric" << endl;
        }
        return;
    }
    if(massege.find("invalid value for metric", 0) != string::npos){
        cout << "invalid value for metric" << endl;
        return;
    }
    // else return seccess massage or other error massege
    if(massege != "vaild input") {
        cout << massege << endl;
    }
}

void ClassifyCommandClient::execute() {
    // oprate the classify command to the server
    char s[2] = "3";
    m_dio->write(s);
    // print un/success massage
    cout << m_dio->read() << endl;
}

void DisplayCommandClient::execute() {
    // oprate the Display command to the server
    char s[2] = "4";
    m_dio->write(s);
    int numLine = 1;
    // get all the tagged from the server
    while (true) {
        // get one tag from the server
        string s = m_dio->read();
        // check if error occure
        if(s.find("please upload data", 0) != string::npos || s.find("please classify the data", 0) != string::npos) {
            cout << s << endl;
            return;
        }
        // check if we recive all the data
        if (s.find("Done", 0) != string::npos) {
            break;
        }
        // if we get a valid tag we print the line using numLine++ and print the tag
        cout << to_string(numLine) + "\t" + s << endl;
        numLine++;
    }
    cout << "Done." << endl;
}

void DownloadCommandClient::execute() {
    // oprate the Download command to the server
    char s[2] = "5";
    m_dio->write(s);
    std::ofstream file;
    string dataFile;
    cin.ignore();
    // Get input for the path to the file we are supposed to write to 
    getline(cin, dataFile);
    string tagForFile;
    while (true) {
        // print a error massege if we don't have a file
        if(tagForFile.find("please upload data", 0) != string::npos) {  
            cout << "please upload data" << endl;
            return;
        }
        // print a error massege if we don't classifiey the data
        if (tagForFile.find("please classify the data", 0) != string::npos) {
            cout << "please classify the data" << endl;
            return;
        }
        // if we get a valid tag we adding space and the tag
        tagForFile += m_dio->read() + " ";
        // check if we recive all the data
        if(tagForFile.find("Done", 0) != string::npos) {
            break;
        }
    }
    // Checks that we got a valid path, if we get only folder, we creat a new file
    file.open(dataFile);
    if (!file.is_open()) {
        dataFile += "/Labeling.txt";
        file.open(dataFile);
        if (!file.is_open()) {
        cout << "invalid pass" << endl;
        return;
        }
    }
    file.close();
    // oprate thread for upload the tagged data to the file
    thread thread(&DownloadCommandClient::writeToFile, this, dataFile, tagForFile);
    thread.detach();     
}

void DownloadCommandClient::writeToFile(const std::string& filePass, const std::string& tagForFile) {
    std::ofstream file;
    file.open(filePass);
    int numLine = 1;
    string tagLine;
    stringstream line(tagForFile);
    // insert all the tagged to tag line one by one 
    while (line >> tagLine) { 
        if(tagLine.find("Done", 0) != string::npos) {
            break;
        }
        // write them to the file
        file << to_string(numLine) + "\t"  + tagLine << endl;
        numLine++;
    }
    file.close();
}
