#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "QVector"
#include "QThread"

class ThreadPool;

class Worker : public QThread {

    Worker(int id):id(id){}
    // fait appel au run de ThreadPoolRunner

protected:
    int id;
};

class ThreadPool {

public:
    ThreadPool(int maxThreadCount = 10){
        this->maxThreadCount = maxThreadCount;
        workers.reserve(maxThreadCount);
    }

    void start(Runnable* runnable){

        if(workers.size() < workers.capacity()){

            workers.push_back(new Worker());
        }

        // cree un thread ou reutilise un existant si un thread
        // est non-utilisé

    }

protected:

    int maxThreadCount;
    QVector<Worker*> workers;

};

#endif // THREADPOOL_H
