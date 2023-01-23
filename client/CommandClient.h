#ifndef COMMAND_CLIENT_H
#define COMMAND_CLIENT_H
#include "../client/ClientClass.h"
#include "DefaultIOCli.h"

class CommandClient {
protected:
    DefaultIOCli* m_dio;
public:
    virtual void execute() = 0;
};

class UploadCommandClient : public CommandClient {
    public:
    UploadCommandClient(DefaultIOCli*);
    void uploadCls(char*);
    void execute();
};

class AlgorithmSettingCommandClient : public CommandClient {
    public:
    AlgorithmSettingCommandClient(DefaultIOCli*);
    void execute();
};

class ClassifyCommandClient : public CommandClient {
    public:
    ClassifyCommandClient(DefaultIOCli*);
    void execute();
};

class DisplayCommandClient : public CommandClient {
    public:
    DisplayCommandClient(DefaultIOCli*);
    void execute();
};

class DownloadCommandClient : public CommandClient {
    public:
    DownloadCommandClient(DefaultIOCli*);
    void writeToFile(const string&, const string&);
    void execute();
};

#endif // COMMAND_CLIENT_H
