#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <iostream>

class DefaultIO {
public:
    virtual std::string read();
    virtual void write(std::string);
};

#endif