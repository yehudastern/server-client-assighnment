#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "ServerClass.hpp"
#include <chrono>
#include <thread>

using namespace std;

std::atomic<bool> stopThreads(false);;

// creat server and do binding with the port, and creat dataBase for the server.
ServerClass::ServerClass(int port) {
    m_server_port = port;
    // set data base.
    //m_input = new GetInput(fileName);
    m_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_sock < 0) {
        sendError("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_server_port);
    if (bind(m_server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        sendError("error binding socket");
        exit(1);
    }
}

// creat connection with specific client
void ServerClass::server_accept() {
    if (listen(m_server_sock, 10) < 0) {
        sendError("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    m_client_sock = accept(m_server_sock, (struct sockaddr *) &client_sin, &addr_len);
    if (m_client_sock < 0) {
        sendError("error accepting client");
    }
}

// get data from the client
string ServerClass::server_recv() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_client_sock, buffer, expected_data_len, 0); 
    string s = string(buffer);
    // check validiation of the data
    if (read_bytes == 0) {
        cout << "closing client socket!" << endl;
        stopThreads = true;
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        string s = "closed";
        return s;
    } else if (read_bytes < 0) {
        cout << "error of recv!" << endl;
        string s = "error";
        return s;
    } else {
        if (s.back() != '\n') {
            s += server_recv();
        }
        return s;
    }
}

void ServerClass::server_send(string str) {
    int sent_bytes = send(m_client_sock, str.c_str(), str.size(), 0);
    if (sent_bytes < 0) {
        sendError("error sending to client");
    }
}

int ServerClass::getClientSock(){
    return m_client_sock;
}

void ServerClass::sendError(string error) {
    // if there's an error closes the socket and leaves
    if (!error.empty()) {
        cout << error << endl;
        close(m_client_sock);
        exit(1);
    }
}