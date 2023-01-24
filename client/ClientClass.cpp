#include "ClientClass.h"

using namespace std;

void ClientClass::checkIp(const char* ip) {
    string s = ip;
    replace(s.begin(), s.end(), '.', ' ');
    istringstream iss(s);
    string num;
    int flag = 0;
    int count = 0;
    while (iss >> num) {
        // Checks that the numbers are indeed numbers
        for (char c : num) {
            if(!isdigit(c)) {
                cout << "Wrong IP argument! please try again :)" << endl;
                exit(1);
            }
        }
        // Checks that the numbers are in the range between 0 and 256
        int number = stoi(num);
        if (number < 0 || number > 256) {
            flag = 1;
        }
        count++;
    }
    // Checks that there are only four numbers
    if (count != 4 || flag) {
        cout << "Wrong IP argument! please try again :)" << endl;
        exit(1);
    }
}

int ClientClass::checkPort(char* port_num) {
    // check that the port is valid integer between 1024 - 65536
    int port = atoi(port_num);
    for (char c : string(port_num)) {
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

ClientClass::ClientClass(const char* ip_address, char* port_no) {
    // creates the socket
    checkIp(ip_address);
    m_ip_address = ip_address;
    m_port_no = checkPort(port_no);
    m_error.clear();
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    // exit if theres an error
    if (m_sock < 0) {
        perror("Error creating socket.");
        exit(1);
    }
}
void ClientClass::connect() {
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
void ClientClass::sendMessage(string message) {
    int sent_bytes = send(m_sock, message.c_str(), message.size(), 0);
    if (sent_bytes < 0) {
        m_error = "sending error";
        sendError();
    }
}

string ClientClass::receiveMessage() {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    // resets the buffer
    memset(&buffer, 0, sizeof(buffer));
    // read the message
    int read_bytes = recv(m_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        m_error = "Connection is closed."; 
        sendError();
    } else if (read_bytes < 0) {
        m_error = "socket error";
        sendError();
    }
    return string(buffer);
}

void ClientClass::sendError() {
    // if there's an error closes the socket and leaves
    if (!m_error.empty()) {
        cout << m_error << endl;
        close(m_sock);
        exit(1);
    }
}
void ClientClass::closeConnection() {
    // if there's an error closes the socket and leaves
    close(m_sock);
    exit(1);
}
