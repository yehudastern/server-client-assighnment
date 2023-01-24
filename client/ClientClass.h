#ifndef CLIENT_CLASS_H
#define CLIENT_CLASS_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <string>

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
    ClientClass(const char* ip_address, char* port_no);
    // connects the client with a server
    void connect();
    // takes a message and send it to the server
    void sendMessage(string);
    // receives message from the server and returns it
    string receiveMessage();
    // checks if there's an error and if so prints it and exit
    void sendError();
    // close the connection with the server
    void closeConnection();
    // checking the port number is correct
    int checkPort(char *port_num);
    // checks the ip is correct
    void checkIp(const char *);
};


#endif
