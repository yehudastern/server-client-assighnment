#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "ServerClass.hpp"
#include <thread>

using namespace std;


// creat server and do binding with the port, and creat dataBase for the server.
ServerClass::ServerClass(int port) {
    // sets port
    m_server_port = port;
    // creates the socket
    m_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // exit if theres an error creating the socket
    if (m_server_sock < 0) {
        cout << "error creating socket" << endl;
        exit(1);
    }
    struct sockaddr_in sin;
    // cleans the struct
    memset(&sin, 0, sizeof(sin));
    // sets the struct
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_server_port);
    // binds the server
    if (bind(m_server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
        exit(1);
    }
}

// creat connection with specific client
void ServerClass::server_accept() {
    // if theres an error listening return
    if (listen(m_server_sock, 10) < 0) {
        cout << "error listening to a socket";
        return;
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    // accepts a client
    m_client_sock = accept(m_server_sock, (struct sockaddr *) &client_sin, &addr_len);
    // returns if theres an error
    if (m_client_sock < 0) {
        cout << "error accepting client";
        return;
    }
}

// get data from the client
string ServerClass::server_recv(int cliIp) {
    char buffer[4096];
    // cleans buffer
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    // gets data using the client socket ip
    int read_bytes = recv(cliIp, buffer, expected_data_len, 0);
    string s = string(buffer);
    // closes socket if its closed
    if (read_bytes == 0) {
        cout << "closing client socket!" << endl;
        close(cliIp);
        string s = "closed";
        return s;
    } else if (read_bytes < 0) {
        // returns if theres a reading error
        sendError("error of recv!", cliIp);
        string s = "error";
        return s;
    } else {
        // gets the messages until there's a \n in the end
        if (s.back() != '\n') {
            s += server_recv(cliIp);
        }
        return s;
    }
}

void ServerClass::server_send(string str, int cliIp) {
    // sends a message using client ip
    int sent_bytes = send(cliIp, str.c_str(), str.size(), 0);
    if (sent_bytes < 0) {
        sendError("error sending to client", cliIp);
    }
}

int ServerClass::getClientSock(){
    return m_client_sock;
}

void ServerClass::sendError(string error, int cliIp) {
    // if there's an error closes the socket and leaves
    if (!error.empty()) {
        cout << error << endl;
        close(cliIp);
    }
}