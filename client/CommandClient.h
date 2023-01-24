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
/*
    file for all the command, using command pattern to execute the knn algorithm
*/

/*
    The "upload data" command is used to upload a dataset to the K-nearest neighbors (KNN) algorithm.
    performance check to the path.
*/  
class UploadCommandClient : public CommandClient {
    public:
    UploadCommandClient(DefaultIOCli*);
    void uploadCls(char*);
    void execute();
};

/*
    set k for K-nearest neighbors (KNN) algorithm, and distance for calculate the nearest vectors,
    performance some check input to vaildete the k and distance is vaild
*/
class AlgorithmSettingCommandClient : public CommandClient {
    public:
    AlgorithmSettingCommandClient(DefaultIOCli*);
    void execute();
};

/*
    classify our unclassified data by our classified data using out seting and knn class
*/
class ClassifyCommandClient : public CommandClient {
    public:
    ClassifyCommandClient(DefaultIOCli*);
    void execute();
};

/*
    get all the tagged that classified from server and print them to the screen.
*/
class DisplayCommandClient : public CommandClient {
    public:
    DisplayCommandClient(DefaultIOCli*);
    void execute();
};

/*
    get all the tagged that classified from server and write them to the file.
*/
class DownloadCommandClient : public CommandClient {
    public:
    DownloadCommandClient(DefaultIOCli*);
    void writeToFile(const string&, const string&);
    void execute();
};

#endif // COMMAND_CLIENT_H
