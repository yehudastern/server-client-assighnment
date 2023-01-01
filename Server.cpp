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

using namespace std;

Server::Server(string fileName, int port) {
    m_server_port = port;
    m_input = new GetInput(fileName);
    m_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_server_port);
    if (bind(m_server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }
}
Server::~Server(){
    delete m_input;
}

void Server::server_accept() { 
    if (listen(m_server_sock, 5) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    m_client_sock = accept(m_server_sock, (struct sockaddr *) &client_sin, &addr_len);
    if (m_client_sock < 0) {
        perror("error accepting client");
    }
}

int Server::server_recv() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        cout << "closing client socket" << endl;
        return 0;
    } else if (read_bytes < 0) {
        cout << "error of recv!" << endl;
        return 0;
    } else {
        m_input->setInfo(buffer);
        return 1;
    }    
}

void Server::server_send() {
    string tag;
    if (m_input->getflag() == 1) {
        Knn myKnn = Knn(m_input->getInputVec(), m_input->getK(), m_input->getDistance());
        tag = myKnn.getTag(m_input->getVec());
        if (myKnn.getFlag() == 0) {
            tag = "invalid input";
        }
    } else {
            tag = "invalid input";
    }
    int sent_bytes = send(m_client_sock, tag.c_str(), tag.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    m_input->setflag();
}

int Server::getClientSock(){
    return m_client_sock;
}
