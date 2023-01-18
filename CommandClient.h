#ifndef COMMAND_CLIENT_H
#define COMMAND_CLIENT_H
#include "ClientClass.h"
class CommandClient {
protected:
    ClientClass* m_client;
public:
    virtual void execute() = 0;
};

class UploadCommandClient : public CommandClient {
    public:
    UploadCommandClient(ClientClass*);
    void execute();
};

class AlgorithmSettingCommandClient : public CommandClient {
    public:
    AlgorithmSettingCommandClient(ClientClass*);
    void execute();
};

class ClassifyCommandClient : public CommandClient {
    public:
    ClassifyCommandClient(ClientClass*);
    void execute();
};

class DisplayCommandClient : public CommandClient {
    public:
    DisplayCommandClient(ClientClass*);
    void execute();
};

class DownloadCommandClient : public CommandClient {
    public:
    DownloadCommandClient(ClientClass*);
    void execute();
};

#endif // COMMAND_CLIENT_H
