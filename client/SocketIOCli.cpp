#include <sstream>
#include "SocketIOCli.h"
#include "DefaultIOCli.h"

SocketIOCli::SocketIOCli (ClientClass* server) {
    m_server = server;
}

string SocketIOCli::read() {
    if (m_v.empty()) {
        string getLines = m_server->receiveMessage();
        istringstream iss(getLines);
        string line;
        while (getline(iss, line)) {
            if (line.empty()) {
                continue;
            }
            m_v.push_back(line);
        }
    }
    string save = m_v.at(0);
    m_v.erase(m_v.begin());
    return save;
}

void SocketIOCli::write(string data) {
    string send = data += "\n";
    m_server->sendMessage(send);
}