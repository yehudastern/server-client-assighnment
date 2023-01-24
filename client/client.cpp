#include "ClientClass.h"
#include "CliClient.h"
#include "SocketIOCli.h"
#include "DefaultIOCli.h"

using namespace std;

int main(int argc, char** argv) {
    // check that we get a vaild number of argument
    if (argc != 3) {
        cout << "please run again with argument" << endl;
        exit(1);
    }
    int num;
    // create a client class
    ClientClass* client = new ClientClass(argv[1], argv[2]);
    // connects to the server
    client->connect(); 
    SocketIOCli dio(client);
    // creat the manage of the client
    CliClient cliClient(&dio);
    // beggin the flow of the program
    cliClient.start();
    // close the connection with the server
    client->closeConnection();
    delete client;
}
