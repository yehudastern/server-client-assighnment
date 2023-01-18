#include "SocketIO.h"

SocketIO::SocketIO (ServerClass* server) {
    m_server = server;
}

string SocketIO::read() {
    string get = m_server->server_recv();
    return get;
}

void SocketIO::write(string data) {
    m_server->server_send(data);
}