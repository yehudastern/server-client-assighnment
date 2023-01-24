#include <sstream>
#include "SocketIOCli.h"
#include "DefaultIOCli.h"

SocketIOCli::SocketIOCli (ClientClass* server) {
    m_server = server;
}
/*
    In order to make sure that we know what information we receive from the server each time,
    an optimization is performed that saves an array of strings with all the read() from the server,
    and with each read() only one message will be received
*/
string SocketIOCli::read() {
    // Checks that we don't have any previous information from the server
    if (m_v.empty()) {
        string getLines = m_server->receiveMessage();
        istringstream iss(getLines);
        string line;
        // Puts all the information from the server into an array of strings,
        // so that every write performed by the server will be read by a single read()
        while (getline(iss, line)) {
            if (line.empty()) {
                continue;
            }
            m_v.push_back(line);
        }
    }
    // return the first string
    string save = m_v.at(0);
    m_v.erase(m_v.begin());
    return save;
}

void SocketIOCli::write(string data) {
    // add /n to the data becuse we want seprate the data by the /n charcter
    string send = data += "\n";
    m_server->sendMessage(send);
}
