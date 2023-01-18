#include "CommandClient.h"

UploadCommandClient::UploadCommandClient(ClientClass* client) {
    m_client = client;
}

AlgorithmSettingCommandClient::AlgorithmSettingCommandClient(ClientClass* client) {
    m_client = client;
}
    
ClassifyCommandClient::ClassifyCommandClient(ClientClass* client) {
    m_client = client;
}

DisplayCommandClient::DisplayCommandClient(ClientClass* client) {
    m_client = client;
}

DownloadCommandClient::DownloadCommandClient(ClientClass* client){
    m_client = client;
}

void UploadCommandClient::execute() {
    m_client->sendMessage("1 done");
    //         cout << m_client->receiveMessage() << endl;
    //         // get 
    //         uploadCls();
    //         cout << m_client->receiveMessage() << endl;
    //         cout << m_client->receiveMessage() << endl;
    //         uploadUnCls();
    cout << m_client->receiveMessage() << endl;
}

void AlgorithmSettingCommandClient::execute() {
    m_client->sendMessage("2 done");
    //         m_client->sendMessage("2");
    //         cin.getline(s, 4096);
    //         client->sendMessage(s);
    cout << m_client->receiveMessage() << endl;
}

void ClassifyCommandClient::execute() {
    m_client->sendMessage("3 done");
    cout << m_client->receiveMessage() << endl;
}

void DisplayCommandClient::execute() {
    m_client->sendMessage("4 done");
    cout << m_client->receiveMessage() << endl;
}

void DownloadCommandClient::execute() {
    m_client->sendMessage("5 done");
    cout << m_client->receiveMessage() << endl;
}