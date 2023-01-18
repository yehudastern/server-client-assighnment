#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "GetInput.hpp"
#include "ManageData.h"
#include "DefaultIO.h"

class Command {
protected:
    ManageData* m_data;
    DefaultIO* m_dio;
    string m_description;
public:
    virtual void execute() = 0;
    string getdescription();
    virtual ~Command();
};

class UploadCommand : public Command {
    public:
    UploadCommand(ManageData* , DefaultIO*);
    void execute();
};

class AlgorithmSettingCommand : public Command {
    public:
    AlgorithmSettingCommand(ManageData* , DefaultIO*);
    void execute();
};

class ClassifyCommand : public Command {
    public:
    ClassifyCommand(ManageData* , DefaultIO*);
    void execute();
};

class DisplayCommand : public Command {
    public:
    DisplayCommand(ManageData* , DefaultIO*);
    void execute();
};

class DownloadCommand : public Command {
    public:
    DownloadCommand(ManageData* , DefaultIO*);
    void execute();
};

#endif