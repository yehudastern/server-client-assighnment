#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <iostream>
using namespace std;

class DefaultIOCli {
public:
    virtual std::string read() = 0;
    virtual void write(std::string) = 0;
    
};


#endif