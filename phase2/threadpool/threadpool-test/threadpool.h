#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "QVector"
#include "QThread"

class ThreadPool;

class Worker : public QThread {

};

class ThreadPool {

public:
    ThreadPool(int maxThreadCount = 10){
        this->maxThreadCount = maxThreadCount;
        workers.reserve(maxThreadCount);
    }

    void start(Runnable* runnable){

    }

protected:

    int maxThreadCount;
    QVector<Worker*> workers;

};

#endif // THREADPOOL_H
