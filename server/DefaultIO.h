#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <iostream>
using namespace std;

// defines an interface for io that the cli uses
class DefaultIO {
public:
    // reads something and returns it
    virtual std::string read() = 0;
    virtual void write(std::string) = 0;
    virtual void closeSocket() = 0;
};


#endif