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
#include "ServerClass.hpp"

class SocketIO : public DefaultIO {
private:
    ServerClass* m_server;
public:
    SocketIO(ServerClass*);
    string read();
    void write(string);
};



#endif