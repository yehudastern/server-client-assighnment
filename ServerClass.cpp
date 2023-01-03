#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include "ServerClass.hpp"
#include "GetInput.hpp"
#include "Knn.hpp"

using namespace std;


// creat server and do binding with the port, and creat dataBase for the server.
ServerClass::ServerClass(string fileName, int port) {
    m_server_port = port;
    // set data base.
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

ServerClass::~ServerClass(){
    delete m_input;
}

// creat connection with specific client
void ServerClass::server_accept() {
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

// get data from the client
int ServerClass::server_recv() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_client_sock, buffer, expected_data_len, 0);
    // check validiation of the data
    if (read_bytes == 0) {
        cout << "closing client socket" << endl;
        return 0;
    } else if (read_bytes < 0) {
        cout << "error of recv!" << endl;
        return 0;
    } else {
        // If the data is valid, sends the data to setInfo for recive organization data
        m_input->setInfo(buffer);
        return 1;
    }    
}

// Processes the information according to knn algorithm and returns the tagged vector to the client.
void ServerClass::server_send() {
    string tag;
    // chece if the data we are recieve is valid
    if (m_input->getflag() == 1) {
        // initialize the Knn algorithem
        Knn myKnn = Knn(m_input->getInputVec(), m_input->getK(), m_input->getDistance());
        tag = myKnn.getTag(m_input->getVec());
        // Checks that the vector was suitable for testing
        if (myKnn.getFlag() == 0) {
            tag = "invalid input";
        }
    } else {
            tag = "invalid input";
    }
    // Sends the tag with a tagged vector, or with an error message when a problem has occurred
    int sent_bytes = send(m_client_sock, tag.c_str(), tag.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    // set flag for the next vector
    m_input->setflag();
}

int ServerClass::getClientSock(){
    return m_client_sock;
}
