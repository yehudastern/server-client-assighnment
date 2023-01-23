#include "ClientClass.h"
#include "CliClient.h"
#include "SocketIOCli.h"
#include "DefaultIOCli.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "please run again with argument" << endl;
        exit(1);
    }
    int num;
    // starts the client
    ClientClass* client = new ClientClass(argv[1], argv[2]);
    // connects to the server
    client->connect(); 
    SocketIOCli dio(client);
    CliClient cliClient(&dio);
    cliClient.start();
    client->closeConnection();
    delete client;
}