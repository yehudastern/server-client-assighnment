#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "ManageData.h"
#include "DefaultIO.h"

// the interface to all the different commands, it has a execute method that is public.
class Command {
protected:
    // puts the data it gets from the user in manage data
    ManageData* m_data;
    // communication method
    DefaultIO* m_dio;
    // the description for the manu
    string m_description;
public:
    virtual void execute() = 0;
    // default method that returns description
    string getdescription();
    virtual ~Command();
};

class UploadCommand : public Command {
    private:
    // gets the data lines to a vector and saves it manage vector (classified)
    int getTrainData();
    // gets the data lines to a vector and saves it manage vector (unclassified)
    int getTestData();
    public:
    // starts the upload command
    UploadCommand(ManageData* , DefaultIO*);
    // deals with the communications and sends to get the train and test data
    void execute();
};

// set the k and distance for knn algorithm
class AlgorithmSettingCommand : public Command {
    public:
    int initDis(string);
    int initK(string num);
    AlgorithmSettingCommand(ManageData* , DefaultIO*);
    void execute();
};

// classified all the unclassified vector and update thier tag
class ClassifyCommand : public Command {
    public:
    ClassifyCommand(ManageData* , DefaultIO*);
    void execute();
};

// send all the tag from unclassified vector to the client
class DisplayCommand : public Command {
    public:
    DisplayCommand(ManageData* , DefaultIO*);
    void execute();
};

// send all the tag from unclassified vector to the client
class DownloadCommand : public Command {
    public:
    DownloadCommand(ManageData* , DefaultIO*);
    void execute();
};


#endif
