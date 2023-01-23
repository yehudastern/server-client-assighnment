#include <iostream>
#include <thread>
#include <vector>
#include "ServerClass.hpp"
#include "SocketIO.h"
#include "Cli.h"

extern std::atomic<bool> stopThreads;

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

void threadFunc(std::reference_wrapper<ServerClass> server) {
    SocketIO* sio_ptr = new SocketIO(&server.get());
    unique_ptr<Cli> cli_ptr (new Cli(sio_ptr));
    cli_ptr->start();
    close(server.get().getClientSock());
}
void manageTreads(std::reference_wrapper<vector<std::thread>> tv) {
    while (true) {
        if (stopThreads) {
            tv.get().front().join();
            tv.get().erase(tv.get().begin());
            stopThreads = false;
        }
    }
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
    int port = checkPort(argv[1]);
    // initialize server with the fike and port
    ServerClass server(port);
    vector<std::thread> tv;
    std::thread manage(manageTreads, std::ref(tv));
    // connect to client in loop
    while (true) {
        server.server_accept();
        tv.emplace_back(threadFunc, std::ref(server));
    }
}
