#include <iostream>
#include "DefaultIO.h"
#include "Command.h"

using namespace std; 

// the cli class has the manage data, the commands and wor
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