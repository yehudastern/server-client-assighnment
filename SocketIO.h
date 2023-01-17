#ifndef SOCKETIO_H
#define SOCKETIO_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "DefaultIO.h"

class SocketIO : public DefaultIO {
private:
    int m_server_port;
    int m_server_sock;
    int m_client_sock;
public:
    SocketIO(int);
    void socketAccept(); 
    int getClientSock();
    string read();
    void write(string);
};



#endif