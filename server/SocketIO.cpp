#include <sstream>
#include "SocketIO.h"

SocketIO::SocketIO (ServerClass* server) {
    m_server = server;
}

string SocketIO::read() {
    if (m_v.empty()) {    
        string getLines = m_server->server_recv();
        istringstream iss(getLines);
        string line;
        while (getline(iss, line)) {
            if (line.empty()) {
                continue;
            }
            m_v.push_back(line);
        }
    }
    string save = m_v.front();
    m_v.erase(m_v.begin());
    return save;
}

void SocketIO::write(string data) {
    m_server->server_send(data += "\n");
}