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
// socket io inherits default io, connects between the socket and some other side. has read, write and close socket.
class SocketIO: public DefaultIO{
private:
    // holds the server
    ServerClass* m_server;
    // hold a list of messages received
    list<string> m_v;
    // holds the client number of the client
    int m_client_ip;
public:
    // constructor
    SocketIO(ServerClass*, int);
    // returns a single message, does so by separating the data by line than storing each chunk in m_v
    virtual std::string read();
    // writes to the server, and adds a \n in the end of each message
    virtual void write(std::string);
    // closes the socket
    virtual void closeSocket();
};


#endif