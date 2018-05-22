#ifndef PRODUCERCONSUMERBUFFER_H
#define PRODUCERCONSUMERBUFFER_H

#include "QSemaphore"
#include "QQueue"
#include "abstractbuffer.h"

template <typename T>
class producerconsumerbuffer : public AbstractBuffer<T>
{
protected:
    QQueue<T> buffer;
    
    
}

#endif // PRODUCERCONSUMERBUFFER_H
