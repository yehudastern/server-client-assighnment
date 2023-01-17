#include <iostream>
#include <unistd.h>
#include "SocketIO.h"
#include "Cli.h"

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

// check that the port is valid integer between 1024 - 65536
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
    if (argc != 2){
        cout << "please run again with an appropriate number of arguments (./server.out port)" << endl;
        exit(1);
    }
    //string fileName = argv[1];
    // check validation of the port and file. 
    //checkFile(argv[1]);
    checkPort(argv[1]);
    int port = checkPort(argv[1]);
    // initialize server with the fike and port
    SocketIO* myServer = new SocketIO(port);
    // connect to client in loop
    while (true) {
        myServer->socketAccept();
        Cli cli = Cli(myServer);
        // Leaves the connection with the client as long as it receives valid message
        // while (myServer->read() != "-1") {
        //     // send the tag to client
        //     myServer->write("test");
        // }
        // close connection if receive invaild massage
        close(myServer->getClientSock());
    }
    return 0;
}