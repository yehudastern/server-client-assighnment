#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    //const int server_port = atoi(argv[2]);
    const int server_port = 27445;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock,(struct sockaddr*) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    while (true) {
        int client_sock = accept(sock, (struct sockaddr*) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            exit(1);
        }
        while (true){
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

        if (read_bytes == 0) {
            cout << "close connection" << endl;
        } else if (read_bytes < 0) {
            cout << "error of recv!" << endl;
            exit(1);
        } else {
            cout << buffer << endl;
        }
        int sent_bytes = send(client_sock, buffer, read_bytes, 0);
        if (sent_bytes < 0 ) {
        perror("error sending to client");
        }
        }
    }
    close(sock);
    return 0;
}


