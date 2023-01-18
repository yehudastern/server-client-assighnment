#ifndef CLI_CLIENT_H
#define CLI_CLIENT_H
#include "ClientClass.h"
#include "CommandClient.h"
#include <vector>

class CliClient {
private:
    ClientClass* m_client;
    vector<CommandClient*> m_commands;
public:
    CliClient(ClientClass*);
    ~CliClient();
    void start();    
};



#endif