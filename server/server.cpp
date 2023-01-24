#include <iostream>
#include <thread>
#include <vector>
#include "ServerClass.hpp"
#include "SocketIO.h"
#include "Cli.h"

using namespace std;

// check that the port is valid integer between 1024 - 65536
int checkPort(char* portInput) {
    int port = atoi(portInput);
    for (char c : string(portInput)) {
        if(!isdigit(c)) {
             cout << "The port is not valid" << endl;
             exit(1);
        }
    } // if the port is not valid leaves
    if (port < 1024 || port > 65536) {
        cout << " The port is not valid" << endl;
        exit(1);
    }
    return port;
}

// the thread function that gets the server starts socket io and server cli and starts cli
void threadFunc(std::reference_wrapper<ServerClass> server, int clientIp) {
    SocketIO* sio_ptr = new SocketIO(&server.get(), clientIp);
    unique_ptr<Cli> cli_ptr (new Cli(sio_ptr));
    try {
        cli_ptr->start();
    } catch (...) {

    }
    close(server.get().getClientSock());
}

// this is opened for every thread and waits to join them
void manageTreads(std::reference_wrapper<std::thread> t) {
    try {
        t.get().join();
    }
    catch (...) {

    }
}

//runs the server, starts new threads for each client, each thread starts cli of each own.
int main(int argc, char *argv[]) {
    // check that we recieve all the necessary arguments
    if (argc != 2){
        cout << "please run again with an appropriate number of arguments (./server.out port)" << endl;
        exit(1);
    }
    // checks if the port is correct
    int port = checkPort(argv[1]);
    // initialize server with the port number
    ServerClass server(port);
    // holds the threads
    vector<std::thread> tv;
    // holds the thread managers that wait to join
    vector<std::thread> mv;
    // connect to client in loop
    while (true) {
        // accepts a client
        server.server_accept();
        // starts the thread and the manage thread vector
        tv.emplace_back(threadFunc, std::ref(server), server.getClientSock());
        mv.emplace_back(manageTreads, std::ref(tv.back()));
    }
}
