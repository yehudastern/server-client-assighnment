#ifndef CLI_CLIENT_H
#define CLI_CLIENT_H
#include "ClientClass.h"
#include "CommandClient.h"
#include <vector>
#include "DefaultIOCli.h"
#include "SocketIOCli.h"

class CliClient {
private:
    DefaultIOCli* m_dio;
    vector<CommandClient*> m_commands;
public:
    CliClient(DefaultIOCli*);
    ~CliClient();
    void start();    
};



#endif