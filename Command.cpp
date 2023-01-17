#include "Command.h"

string Command::getdescription(){
    return m_description;
}

Command::Command(ManageData* data, DefaultIO* dio): m_data(data), m_dio(dio) {}

UploadCommand::UploadCommand(ManageData* data, DefaultIO* dio): Command(data,dio) {
    m_description = "1. upload an unclassified csv data file";
} 

AlgorithmSettingCommand::AlgorithmSettingCommand(ManageData* data, DefaultIO* dio): Command(data,dio) {
    m_description = "2. algorithm settings";
} 

ClassifyCommand::ClassifyCommand(ManageData* data, DefaultIO* dio): Command(data,dio) {
    m_description = "3. classify data";
} 

DisplayCommand::DisplayCommand(ManageData* data, DefaultIO* dio): Command(data,dio) {
    m_description = "4. display results";
} 

DownloadCommand::DownloadCommand(ManageData* data, DefaultIO* dio): Command(data,dio) {
    m_description = "5. download results";
} 