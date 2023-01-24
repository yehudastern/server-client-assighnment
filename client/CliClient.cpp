#include <limits>
#include "CliClient.h"


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
    while(true) {
        cout << "Welcome to the KNN Classifier Server. Please choose an option:" << endl;
        for (size_t i = 0; i < 6; i++) {
            cout << m_dio->read() << endl;
        }
        // prints the message from the server
        int flag = 1;
        int num;
        while (flag) {
            if(cin >> num) {
                if (num <= 5 && num > 0) {
                    m_commands[num-1]->execute();
                    flag = 0;
                } else if (num == 8) {
                    char s[2] = "8";
                    m_dio->write(s);
                    return;
                } else {
                    cout << "invaild input! please insert again:" << endl;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invaild input! please insert again:" << endl;
            }
        }
        // int flag = 1;
        // int num;
        // cin >> num;
        // while (flag) {
        //     if (num <= 5 && num > 0) {
        //         m_commands[num-1]->execute();
        //         flag = 0;
        //     } else if (num == 8) {
        //         char s[2] = "8";
        //         m_dio->write(s);
        //         return;
        //     } else {
        //         cout << "invaild input! please insert again:" << endl;
        //         cin.ignore();
        //         cin >> num;
        //     }
        // }
    }
} 