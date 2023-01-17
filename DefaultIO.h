#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <iostream>
using namespace std;

class DefaultIO {
public:
    virtual std::string read();
    virtual void write(std::string);
};

#endif