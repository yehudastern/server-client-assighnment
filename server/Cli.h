#include <iostream>
#include "DefaultIO.h"
#include "Command.h"

using namespace std; 

class Cli {
private:
    DefaultIO* m_dio;
    ManageData* m_data;
    vector<Command*> m_commands;
public:
    void start();
    Cli(DefaultIO*);
    ~Cli();
};