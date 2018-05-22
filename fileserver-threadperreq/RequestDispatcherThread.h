#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H

#include "request.h"
#include "abstractbuffer.h"



class requestdispatcherthread: public QThread
{
public:
    requestdispatcherthread();

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;

};

#endif // REQUESTDISPATCHERTHREAD_H
