#include <sstream>
#include "SocketIO.h"
extern std::atomic<bool> stopThreads;

SocketIO::SocketIO (ServerClass* server, int ip) {
    m_server = server;
    m_client_ip = ip;
}

string SocketIO::read() {
    if (m_v.empty()) {    
        string getLines = m_server->server_recv(m_client_ip);
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

void SocketIO::closeThread() {
    stopThreads = true;
    close(m_client_ip);
}

void SocketIO::write(string data) {
    m_server->server_send(data += "\n", m_client_ip);
}