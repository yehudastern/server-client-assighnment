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

/*
    socketIO He is responsible for communicating with the server,
    has a communication field and another field for saving the information we receive from the server.
*/
class SocketIOCli: public DefaultIOCli{
private:
    ClientClass* m_server;
    vector<string> m_v;
public:
    SocketIOCli(ClientClass*);
    // get data from the user
    virtual std::string read();
    // send data to the user
    virtual void write(std::string);
    void close();
};

#endif
