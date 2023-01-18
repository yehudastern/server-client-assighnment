#include "ClientClass.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3){
        cout << "please run again with argument" << endl;
        exit(1);
    }
    int num;
    char s[4096];
    ClientClass client(argv[1], argv[2]); // starts the client
    client.connect(); // connects to the server
    while(true) {
        // prints the message from the server
        for (size_t i = 0; i < 5; i++) {
            cout << client.receiveMessage() << endl;
        }
        cin >> num;
        switch (num){
        case 1:
            client.sendMessage("1");
            cout << client.receiveMessage() << endl;
            // get 
            uploadCls();
            cout << client.receiveMessage() << endl;
            cout << client.receiveMessage() << endl;
            uploadUnCls();
            break;
        case 2:
            client.sendMessage("2");
            cin.getline(s, 4096);
            client.sendMessage(s);
            break;
        case 3:
            client.sendMessage("3");
            cin.getline(s, 4096);
            client.sendMessage(s); 
        case 4:

            break;
        case 5:

            break;
        case 8:
            client.sendMessage("-1");
            break;
        default:
            cout << "invaild input!" <<endl;
            break;
        }
    }
}