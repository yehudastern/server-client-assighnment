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
    // check that we have a data
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data");
        return;
    }
    // checks the k is not too much biggest
    if(m_data->getK() > m_data->getClassified().size()){
        m_dio->write("please replace k or file");
        return;
    }
    // creat the knn algorithm with our setting
    Knn myKnn = Knn(m_data->getClassified(),  m_data->getK(), m_data->getDistance());
    vector<pair<vector<double>,string>> vec;
    // classifiy all vector from the unclassified vectors
    for(pair<vector<double>,string> i : m_data->getUnclassified()) {
       string tag;
       // classifiy specipic vecror
       tag = myKnn.getTag(i.first);
       // if error occur send massage, and terminate the classify
       if (myKnn.getFlag() == 0) {
           m_dio->write("invalid classified, please upload appropriate files");
           return;
       }
       // put the vector and the apropriate tag
       vec.push_back(make_pair(i.first, tag));
    }
    m_data->setUnclassified(vec);
    m_dio->write("classifying data complete");
}

DisplayCommand::DisplayCommand(ManageData* data, DefaultIO* dio) {
    m_description = "4. display results";
    m_data = data;
    m_dio = dio;
}

void DisplayCommand::execute() {
    // check that we upload data
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data"); 
        return;  
    }
    // check that we classify data
    if (m_data->getUnclassified().at(0).second.empty()) {
        m_dio->write("please classify the data"); 
        return;
    }
    // send all the tag to the client
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
     // check that we upload data
    if (m_data->getClassified().empty()) {
        m_dio->write("please upload data"); 
        return;  
    }
    // check that we classify data
    if (m_data->getUnclassified().back().second.empty()) {
        m_dio->write("please classify the data"); 
        return;
    }
    // send all the tag to the client
    for(pair<vector<double>,string> i : m_data->getUnclassified()) {
        m_dio->write(i.second);
    }
    m_dio->write("Done.");
}

Command::~Command() {

}
