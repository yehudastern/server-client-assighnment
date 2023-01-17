#include "SocketIO.h"

SocketIO::SocketIO(int port) {
    m_server_port = port;
    m_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_server_port);
    if (bind(m_server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }
}

// creat connection with specific client
void SocketIO::socketAccept() {
    if (listen(m_server_sock, 10) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    m_client_sock = accept(m_server_sock, (struct sockaddr *) &client_sin, &addr_len);
    if (m_client_sock < 0) {
        perror("error accepting client");
    }
}

string SocketIO::read() {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_client_sock, buffer, expected_data_len, 0);
    // check validiation of the data
    if (read_bytes == 0) {
        cout << "closing client socket" << endl;
        return "-1";
    } else if (read_bytes < 0) {
        cout << "error of recv!" << endl;
        return "-1";
    } else {
        // If the data is valid, sends the data to setInfo for recive organization data
        return buffer;
    }
}

void SocketIO::write(string data) {
    // Sends the tag with a tagged vector, or with an error message when a problem has occurred
    int sent_bytes = send(m_client_sock, data.c_str(), data.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}


int SocketIO::getClientSock(){
    return m_client_sock;
}