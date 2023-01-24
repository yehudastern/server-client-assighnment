#include <limits>
#include "CliClient.h"

/*
   creat the manage of the client,  with field of m_dio: (socket for connection with the server),
   m_commands: (array of command to performance the command).
*/
CliClient::CliClient(DefaultIOCli* dio) {
    m_dio = dio;
    m_commands = {new UploadCommandClient(m_dio), new AlgorithmSettingCommandClient(m_dio), new ClassifyCommandClient(m_dio), 
    new DisplayCommandClient(m_dio), new DownloadCommandClient(m_dio)};
}

CliClient::~CliClient() {
    for (auto &i : m_commands) {
        delete i;
    }
}

void CliClient::start() {
    // print the menu 
    while(true) {
        cout << "Welcome to the KNN Classifier Server. Please choose an option:" << endl;
        for (size_t i = 0; i < 6; i++) {
            // get description of the command from the server
            cout << m_dio->read() << endl;
        }
        int flag = 1;
        int num;
        while (flag) {
            // get a number from the user
            if(cin >> num) {
                // check that the number is in the range 1-5, and performs the appropriate task
                if (num <= 5 && num > 0) {
                    m_commands[num-1]->execute();
                    flag = 0;
                } else if (num == 8) {
                    // if we recive 8 terminate the client
                    char s[2] = "8";
                    m_dio->write(s);
                    return;
                // if we recieve other num input, print error massage and get anothr input.    
                } else {
                    cout << "invaild input! please insert again:" << endl;
                }
            // if we recieve non number input, print error massage and get anothr input.    
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invaild input! please insert again:" << endl;
            }
        }
    }
} 
