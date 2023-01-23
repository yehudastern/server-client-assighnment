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
        // prints the message from the server
        for (size_t i = 0; i < 6; i++) {
            cout << m_dio->read() << endl;
        }
        int flag = 1;
        while (flag) {
            int num;
            //cin.ignore();
            cin >> num;
            if (num <=5 && num > 0) {
                m_commands[num-1]->execute();
                flag = 0;
            } else if (num == 8) {
                char s[2] = "8";
                m_dio->write(s);
                return;
            } else {
                cout << "invaild input! please insert again:" <<endl;
                flag = 0;
            }
        }
    }
} 