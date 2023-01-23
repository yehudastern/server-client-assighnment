#ifndef SOCKETIO_H
#define SOCKETIO_H

#include "ServerClass.hpp"
#include <iostream>
#include "DefaultIO.h"
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <list>

using namespace std;
class SocketIO: public DefaultIO{
private:
    ServerClass* m_server;
    list<string> m_v;
public:
    SocketIO(ServerClass*);
    virtual std::string read();
    virtual void write(std::string);
};


#endif