#include "Cli.h"

using namespace std;

Cli::Cli(DefaultIO* io) {
    m_dio = io;
    m_data = new ManageData();
    m_commands = {new UploadCommand(m_data, m_dio), new AlgorithmSettingCommand(m_data, m_dio), new ClassifyCommand(m_data, m_dio),
                  new DisplayCommand(m_data, m_dio), new DownloadCommand(m_data, m_dio)};
    ManageData getManageData;
    vector<Command*> getCommands;
}

void Cli::start() {
    while(true) {
        string menu;
        for (int i = 0; i <  5; i++) {
           m_dio->write(m_commands[i]->getdescription());
        }
        m_dio->write("8. exit");
        // m_dio->write(menu);
        string s = m_dio->read();
        if (s.empty()) {
            return;
        }
        int num = stoi(s);
        if (num <= 5) {
            m_commands[num-1]->execute();
        } else if (num == 8) {
            return;
        }
    }
}

Cli::~Cli() {
    for (auto i : m_commands) {
        delete i;
    }
    delete m_data;
}