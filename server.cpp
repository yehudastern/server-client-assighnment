#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "GetInput.hpp"
#include "Knn.hpp"
#include "DistanceFactory.hpp"

using namespace std;
void server(string fileName, int port) {
    const int server_port = port;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }
    GetInput* input = new GetInput(fileName);
    while (true) {
        if (listen(sock, 5) < 0) {
            perror("error listening to a socket");
        }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            break;
        }
        while (true) {
            string tag;
            char buffer[4096];
            memset(buffer, 0, sizeof buffer);
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                cout << "closing client socket" << endl;
                break;
            } else if (read_bytes < 0) {
                cout << "error of recv!" << endl;
                break;
            } else {
                input->setInfo(buffer);
                if (input->getflag() == 1) {
                    Knn myKnn = Knn(input->getInputVec(), input->getK(), input->getDistance());
                    tag = myKnn.getTag(input->getVec());
                    if (myKnn.getFlag() == 0) {
                        tag = "invalid input";
                    }
                } else {
                    tag = "invalid input";
                }

            } int sent_bytes = send(client_sock, tag.c_str(), tag.size(), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
        }
        close(client_sock);
    }
    delete input;
}


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

int main(int argc, char *argv[]) {
    string fileName = argv[1];
    //cout << "file name: " << fileName << " port: " << argv[2] << endl;
    checkFile(argv[1]);
    int port = atoi(argv[2]);
    server(fileName, port);
//    GetInput* input = new GetInput(fileName);
//    input->setInfo("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 MAN 0");
//    string tag;
//    if (input->getflag() == 0) {
//        Knn myKnn = Knn(input->getInputVec(), input->getK(), input->getDistance());
//        tag = myKnn.getTag(input->getVec());
//        if (myKnn.getFlag() == 0) {
//            tag = "invalid input";
//        }
//    } else {
//        tag = "invalid input";
//    }
//    cout << tag;
//    cout << input->getflag() << endl;
//    delete input;
    return 0;
}

//cout << buffer << endl;
////GetInput input = GetInput(fileName, buffer);
//
////                if (input.getflag() == 0) {
////                    Knn myKnn = Knn(input.getInputVec(), input.getK(), input.getDistance());
////                    tag = myKnn.getTag(input.getVec());
////                    if (myKnn.getFlag() == 0) {
////                        tag = "invalid input";
////                    }
////                } else {
////                    tag = "invalid input";
////                }
//}
//int sent_bytes = send(client_sock, tag.c_str(), tag.size(), 0);
