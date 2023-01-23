#ifndef SOCKETIOCLIENT_H
#define SOCKETIOCLIENT_H

#include <iostream>
#include "DefaultIOCli.h"
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <vector>
#include "ClientClass.h"

class SocketIOCli: public DefaultIOCli{
private:
    ClientClass* m_server;
    vector<string> m_v;
public:
    SocketIOCli(ClientClass*);
    virtual std::string read();
    virtual void write(std::string);
    void close();
};


#endif