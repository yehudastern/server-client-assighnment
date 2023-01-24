#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <atomic>
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
    string server_recv(int);
    void server_send(string, int);
    int getClientSock();
    void sendError(string, int);
};

#endif //SERVER_H
