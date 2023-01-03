#include "ClientClass.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3){
        cout << "please run again with argument" << endl;
        exit(1);
    }
    ClientClass client(argv[1], argv[2]); // starts the client
    client.connect(); // connects to the server
    while(true) {
        char data_addr[4090];
        // takes a message from the user
        scanf(" %[^\n]", data_addr);
        client.sendMessage(data_addr); // sends a message
        cout << client.receiveMessage() << endl; // prints the message from the server
    }
}