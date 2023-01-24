#include <sstream>
#include "SocketIO.h"

SocketIO::SocketIO (ServerClass* server, int ip) {
    m_server = server;
    m_client_ip = ip;
}

string SocketIO::read() {
    // if theres no messages, grabs messages and splits them by \n
    if (m_v.empty()) {    
        string getLines = m_server->server_recv(m_client_ip);
        // splits by lines
        istringstream iss(getLines);
        string line;
        while (getline(iss, line)) {
            // ignores empty lines
            if (line.empty()) {
                continue;
            }
            m_v.push_back(line);
        }
    }
    // returns the first message to come and removes it
    string save = m_v.front();
    m_v.erase(m_v.begin());
    return save;
}
// closes the socket
void SocketIO::closeSocket() {
    close(m_client_ip);
}

void SocketIO::write(string data) {
    // sends with \n to separate messages
    m_server->server_send(data += "\n", m_client_ip);
}