#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
class ClientClass {
private:
    // stores either an empty string or an error
    string m_error;
    // the ip address
    const char* m_ip_address;
    // the port number
    int m_port_no;
    // the socket
    int m_sock;
public:
    // creates a client socket
    ClientClass(const char* ip_address, const int port_no);
    // connects the client with a server
    void connect();
    // takes a message and send it to the server
    void sendMessage(char data_addr[4090]);
    // receives message from the server and returns it
    string receiveMessage();
    // checks if there's an error and if so prints it and exit
    void sendError();
};


#endif //CLIENT_H
