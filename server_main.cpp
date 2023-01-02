#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "GetInput.hpp"
#include "Knn.hpp"
#include "Server.hpp"

using namespace std;

void checkFile(char* fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        file.close();
        return;
    } else {
        // exit the program
        cout << "wrong file name!" << endl;
        exit(1);
    }
}

int checkPort(char* portInput) {
    int port = atoi(portInput);
    for (char c : string(portInput)) {
        if(!isdigit(c)) {
             cout << "The port is not valid" << endl;
             exit(1);
        }
    }
    if (port < 1024 || port > 65536) {
        cout << " The port is not valid" << endl;
        exit(1);
    }
    return port;
}

int main(int argc, char *argv[]) {
    string fileName = argv[1];
    checkFile(argv[1]);
    checkPort(argv[2]);
    int port = checkPort(argv[2]);
    Server myServer = Server(fileName, port);
    while (true) {
        myServer.server_accept();
        while (myServer.server_recv()){
            myServer.server_send();
        }
        close(myServer.getClientSock());
    }
    return 0;
}