#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "ServerClass.hpp"
#include "GetInput.hpp"
#include "Knn.hpp"

class ServerClass {
private:
    int m_server_port;
    int m_server_sock;
    int m_client_sock;
    // stores either an empty string or an error
public:
    ServerClass(int port);
    void server_accept(); 
    string server_recv();
    void server_send(string);
    int getClientSock();
    void sendError(string error);
};

#endif //SERVER_H


