#include "CliClient.h"

CliClient::CliClient(ClientClass* client) {
    m_client = client;
    m_commands = {new UploadCommandClient(m_client), new AlgorithmSettingCommandClient(m_client), new ClassifyCommandClient(m_client), 
    new DisplayCommandClient(m_client), new DownloadCommandClient(m_client)};
}

CliClient::~CliClient() {
    for (auto &i : m_commands) {
        delete i;
    }
}

void CliClient::start() {
    while(true) {
        // prints the message from the server
        for (size_t i = 0; i < 5; i++) {
            cout << m_client->receiveMessage() << endl;
            cout << "trying" << endl;
        }
        int flag = 1;
        while (flag){
            int num;
            string s;
            cin >> num;
            if (num <=5 && num > 0) {
                m_commands[num-1]->execute();
                flag = 0;
            } else if (num == 8){
                s = "8";
                m_client->sendMessage(s);
                m_client->closeConnection();
                return;
            } else {
                cout << "invaild input! please insert again:" <<endl;
            }
        }
    }
    //     switch (num){
    //     case 1:
    //         m_client->sendMessage("1");
    //         cout << m_client->receiveMessage() << endl;
    //         // get 
    //         uploadCls();
    //         cout << m_client->receiveMessage() << endl;
    //         cout << m_client->receiveMessage() << endl;
    //         uploadUnCls();
    //         break;
    //     case 2:
    //         m_client->sendMessage("2");
    //         cin.getline(s, 4096);
    //         client->sendMessage(s);
    //         break;
    //     case 3:
    //         client->sendMessage("3");
    //         cin.getline(s, 4096);
    //         client->sendMessage(s); 
    //     case 4:

    //         break;
    //     case 5:

    //         break;
    //     case 8:
    //         client->sendMessage("-1");
    //         break;
    //     default:
    //         cout << "invaild input!" <<endl;
    //         break;
    //     }
    // }
} 