#include <iostream>
#include "DefaultIO.h"
#include "Command.h"

using namespace std; 

class Cli {
private:
    DefaultIO* m_dio;
    ManageData* m_data;
    vector<Command*> m_commands;
public:
    Cli(DefaultIO*);
    ~Cli();
};

Cli::Cli(DefaultIO* io) {
    m_dio = io;
    m_data = new ManageData();
    m_commands = {new UploadCommand(m_data, m_dio), new AlgorithmSettingCommand(m_data, m_dio), new ClassifyCommand(m_data, m_dio), 
    new DisplayCommand(m_data, m_dio), new DownloadCommand(m_data, m_dio)};
    ManageData getManageData();
    vector<Command*> getCommands();
}

Cli::~Cli() {
    for (auto &i : m_commands) {
        delete i;
    }
    delete m_data;
    delete m_dio;
}
