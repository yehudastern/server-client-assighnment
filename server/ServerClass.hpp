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
#include "Knn.hpp"

// this class hides the implementation of of the server and its communications with the client
class ServerClass {
private:
    // the servers port
    int m_server_port;
    // the servers socket
    int m_server_sock;
    // the client socket
    int m_client_sock;
    // stores either an empty string or an error
public:
    // creates sockets and binds it
    ServerClass(int port);
    // accepting a client
    void server_accept();
    // getting a string from given client
    string server_recv(int);
    // sending a message to a given client
    void server_send(string, int);
    // getting recent client socket
    int getClientSock();
    // prints an error and closes given client
    void sendError(string, int);
};

#endif //SERVER_H
