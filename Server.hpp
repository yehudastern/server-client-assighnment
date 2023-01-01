#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "Server.hpp"
#include "GetInput.hpp"
#include "Knn.hpp"

class Server {
private:
    int m_server_port;
    int m_server_sock;
    int m_client_sock;
    GetInput* m_input;
public:
    Server(string fileName, int port);
    void server_accept(); 
    int server_recv();
    void server_send();
    int getClientSock();
    ~Server();
};

#endif //SERVER_H


