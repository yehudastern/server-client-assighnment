#include "Cli.h"

using namespace std;

Cli::Cli(DefaultIO* io) {
    m_dio = io;
    m_data = new ManageData();
    // starts the commands
    m_commands = {new UploadCommand(m_data, m_dio), new AlgorithmSettingCommand(m_data, m_dio), new ClassifyCommand(m_data, m_dio),
                  new DisplayCommand(m_data, m_dio), new DownloadCommand(m_data, m_dio)};
}

void Cli::start() {
    // keeps looping until the client exits with 8
    while(true) {
        // prints the menu for each command
        for (int i = 0; i <  5; i++) {
           m_dio->write(m_commands[i]->getdescription());
        }
        m_dio->write("8. exit");
        // reads the number the client chose
        string s = m_dio->read();
        // if the number is empty returns
        if (s.empty()) {
            return;
        }
        // converts the string to a number
        int num = stoi(s);
        // if the number is one of the commands excecutes them
        if (num <= 5) {
            m_commands[num-1]->execute();
        } // leaves if we get 8
        else if (num == 8) {
            m_dio->closeSocket();
            return;
        }
    }
}

Cli::~Cli() {
    // deletes the commands
    for (auto i : m_commands) {
        delete i;
    }
    // deletes the manage data
    delete m_data;
}