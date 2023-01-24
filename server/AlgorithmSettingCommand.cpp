#include "Command.h"
#include <fstream>
#include <string>
#include <sstream>

AlgorithmSettingCommand::AlgorithmSettingCommand(ManageData* data, DefaultIO* dio) {
    m_description = "2. algorithm settings\n";
    m_data = data;
    m_dio = dio;
}

int AlgorithmSettingCommand::initDis(string disType) {
    // check that we get valid input from the client, and initialize the distance
    if (!((disType == "AUC") || (disType == "MAN") || (disType == "CHB")|| (disType == "CAN" )|| (disType == "MIN"))) {
        return 0;
    } else {
        return 1;
    }
}

int AlgorithmSettingCommand::initK(string num) {
    for (char c : num) {
        if(!isdigit(c)){
            return 0;
        }
    }
    if (!m_data->getClassified().empty()){
        if (m_data->getClassified().size() < stoi(num)) {
            return 0;
        }
    }
    if(stoi(num) <= 0) {
        return 0;
    }
    return 1;
}

void AlgorithmSettingCommand::execute() {
    string s = string("The current KNN parameters are: K = ") + to_string(m_data->getK()) +
               string(", distance metric = ") + m_data->getDisString();
    m_dio->write(s);
    string line = m_dio->read();
    if(line == string("save the current parameters")) {
        m_dio->write(string("vaild input"));
        return;
    }
    // making a string stream in order to saparate the spaces
    istringstream iss(line);
    string k;
    string dis;
    string fail;
    iss >> k;
    iss >> dis;
    if (iss >> fail) {
        m_dio->write(string("too many arguments inserted"));
    } else if (!k.empty() && !dis.empty()) {
        if((initK(k) || initK(dis)) && (initDis(dis) || initDis(k))) {
            if (initK(k)) {
                m_data->setK(stoi(k));
                m_data->setDistance(new DistanceFactory(dis));
                m_data->setDisString(dis);
            } else {
                m_data->setK(stoi(dis));
                m_data->setDistance(new DistanceFactory(k));
                m_data->setDisString(k);
            }
            m_dio->write(string("vaild input"));
            return;
        }
        string msg;
        if (!(initK(k) || initK(dis))) {
            msg = string("invalid value for K");
        }
        if (!(initDis(dis) || initDis(k))) {
            msg += string("invalid value for metric");
        }
        m_dio->write(msg);
    } else {
        m_dio->write(string("few argument insert"));
    }
}
 //iris_classified.csv
 //iris_Unclassified.csv