#include "Command.h"

string Command::getdescription(){
    return m_description;
}

UploadCommand::UploadCommand(ManageData* data, DefaultIO* dio){
    m_description = "1. upload an unclassified csv data file";
    m_data = data;
}

void UploadCommand::execute() {
    m_dio->write("1 done");
}

AlgorithmSettingCommand::AlgorithmSettingCommand(ManageData* data, DefaultIO* dio) {
    m_description = "2. algorithm settings";
    m_data = data;
    m_dio = dio;
}
void AlgorithmSettingCommand::execute() {
    m_dio->write("2 done");
}

ClassifyCommand::ClassifyCommand(ManageData* data, DefaultIO* dio) {
    m_description = "3. classify data";
    m_data = data;
    m_dio = dio;
}
void ClassifyCommand::execute() {
    m_dio->write("3 done");
}

DisplayCommand::DisplayCommand(ManageData* data, DefaultIO* dio) {
    m_description = "4. display results";
    m_data = data;
    m_dio = dio;
}
void DisplayCommand::execute() {
    m_dio->write("4 done");
}

DownloadCommand::DownloadCommand(ManageData* data, DefaultIO* dio) {
    m_description = "5. download results";
    m_data = data;
    m_dio = dio;
}
void DownloadCommand::execute() {
    m_dio->write("5 done");
}

Command::~Command() {

}
