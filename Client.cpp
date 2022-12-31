#include "Client.h"

using namespace std;
Client::Client(const char* ip_address, const int port_no) {
    // creates the socket
    m_ip_address = ip_address;
    m_port_no = port_no;
    m_error.clear();
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    // exit if theres an error
    if (m_sock < 0) {
        perror("Error creating socket.");
        exit(1);
    }
}
void Client::connect() {
    struct sockaddr_in sin;
    // resets sin to zeros
    memset(&sin, 0, sizeof(sin));
    // takes the info
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_ip_address);
    sin.sin_port = htons(m_port_no);
    // checks if there's an error
    if (::connect(m_sock, (struct sockaddr*) &sin, sizeof(sin)) < 0) {
        m_error = "Error connecting to server.";
        sendError();
    }
}
void Client::sendMessage(char data_addr[4090]) {
    // if user entered -1 sends an empty string to the server to shut the socket down
    if (strncmp(data_addr, "-1", 2) == 0) {
        char empty[] = "";
        int zeroLen = 0;
        int sent_bytes = send(m_sock, empty, zeroLen, 0);
        if (sent_bytes < 0) {
            m_error = "sending error";
            sendError();
        }
        // adds an error message
        m_error = "Closing socket.";
        sendError();
    }
    // sends the message
    int data_len = strlen(data_addr);
    int sent_bytes = send(m_sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        m_error = "sending error"; // error
        sendError();
    }
}

string Client::receiveMessage() {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    // resets the buffer
    memset(&buffer, 0, sizeof(buffer));
    // read the message
    int read_bytes = recv(m_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        m_error = "Connection is closed."; // connection is closed
        sendError();
    } else if (read_bytes < 0) {
        m_error = "socket error";
        sendError();
    } else {
        // returns the message
        return buffer;
    }
}

void Client::sendError() {
    // if there's an error closes the socket and leaves
    if (!m_error.empty()) {
        cout << m_error << endl;
        close(m_sock);
        exit(1);
    }
}