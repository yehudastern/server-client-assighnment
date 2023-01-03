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

// check that file is exist
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

// check that the port is valid integer bitween 1024 - 65536
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
    // check that we recieve all the necessary arguments
    if (argc != 3){
        cout << "please run again with argument" << endl;
        exit(1);
    }
    string fileName = argv[1];
    // check validation of the port and file. 
    checkFile(argv[1]);
    checkPort(argv[2]);
    int port = checkPort(argv[2]);
    // initialize server with the fike and port
    Server myServer = Server(fileName, port);
    // connect to client in loop
    while (true) {
        myServer.server_accept();
        // Leaves the connection with the client as long as it receives valid message
        while (myServer.server_recv()) {
            // send the tag to client
            myServer.server_send();
        }
        // close connection if receive invaild massage
        close(myServer.getClientSock());
    }
    return 0;
}