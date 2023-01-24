#include <iostream>
#include "DefaultIO.h"
#include "Command.h"

using namespace std; 

/*
 * cli communicates with the client and starts the commands to do the requests of the client
 */
class Cli {
private:
    DefaultIO* m_dio;
    ManageData* m_data;
    vector<Command*> m_commands;
public:
    // starts the program
    void start();
    // gets the communication method
    Cli(DefaultIO*);
    ~Cli();
};