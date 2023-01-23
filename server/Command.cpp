#include "Command.h"
#include "Knn.hpp"

string Command::getdescription(){
    return m_description;
}

ClassifyCommand::ClassifyCommand(ManageData* data, DefaultIO* dio) {
    m_description = "3. classify data";
    m_data = data;
    m_dio = dio;
}

void ClassifyCommand::execute() {
    if(m_data->getK() > m_data->getClassified().size()){
        m_dio->write("please replace k or file");
        return;
    }
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data"); 
        return;  
    }
    Knn myKnn = Knn(m_data->getClassified(),  m_data->getK(), m_data->getDistance());
    vector<pair<vector<double>,string>> vec;
  //  int test = 1;
    for(pair<vector<double>,string> i : m_data->getUnclassified()) {
       string tag;
       tag = myKnn.getTag(i.first);
       if (myKnn.getFlag() == 0) {
           // cout << test << endl;
           m_dio->write("invalid classified");
           return;
       }
       vec.push_back(make_pair(i.first, tag));
       m_data->setUnclassified(vec);
     //  test++;
    }
    m_dio->write("classifying data complete");
}

DisplayCommand::DisplayCommand(ManageData* data, DefaultIO* dio) {
    m_description = "4. display results";
    m_data = data;
    m_dio = dio;
}

void DisplayCommand::execute() {
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data"); 
        return;  
    }
    if (m_data->getUnclassified().at(0).second.empty()) {
        m_dio->write("please classify the data"); 
        return;
    }
    for(pair<vector<double>,string> i : m_data->getUnclassified()) {
        m_dio->write(i.second);
    }
    m_dio->write("Done.");
}

DownloadCommand::DownloadCommand(ManageData* data, DefaultIO* dio) {
    m_description = "5. download results";
    m_data = data;
    m_dio = dio;
}
void DownloadCommand::execute() {
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data"); 
        return;  
    }
    if (m_data->getUnclassified().back().second.empty()) {
        m_dio->write("please classify the data"); 
        return;
    }
    int numLine = 1;
    for(pair<vector<double>,string> i : m_data->getUnclassified()) {
        m_dio->write(i.second);
    }
    m_dio->write("Done.");
}

Command::~Command() {

}