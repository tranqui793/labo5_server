#ifndef ABSTRACTBUFFER_H
#define ABSTRACTBUFFER_H

#include "qsemaphore.h"

template<typename T>
class AbstractBuffer {
public:
    virtual void put(T item)= 0;
    virtual T get() = 0;
    virtual bool tryPut(T item)= 0;

};

#endif // ABSTRACTBUFFER_H
