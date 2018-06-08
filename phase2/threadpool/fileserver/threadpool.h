#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QWaitCondition>
#include<QSemaphore>
#include<QMutex>
#include "runnable.h"
#include "QVector"
#include "QThread"
#include "QMutex"
#include "QWaitCondition"

class ThreadPool;

/** \class      Worker
*   \authors    Adam Zouari et Oussama Lagha
*   \date       25 Mai 2018
*   \brief      Implementation du comportement des threads du threadPool
*/
class Worker : public QThread {

public:

    /**
    *   \brief          Constructeur de Worker
    *   \param request  Tache attribué au thread
    */
    Worker(Runnable* request): request(request), isWorking(true){}
    // fait appel au run de requestrunnable


    /**
    *   \brief          Comportement du Worker
    */
    void run(){

        while(getIsWorking()){
            mutex.lock();
            request->run();
            //on met isWorking a false quand il fini le run de la request
            isWorking = false;
            mutex.unlock();
        }
    }

    /**
    *   \brief          Retourne le statut du worker
    */
    bool getIsWorking(){
        return isWorking;
    }

    /**
    *   \brief          Attribue une nouvelle tache au Worker
    *   \param  request Tache à attribuée au worker
    */
    void setWork(Runnable* request){
        mutex.lock();
        isWorking = true;
        this->request = request;
        mutex.unlock();
    }

    /**
    *   \brief          Destructeur du Worker
    */
    ~Worker(){
        delete request;
        this->setTerminationEnabled();

    }

protected:

    Runnable* request;       // requete à traitée
    bool isWorking;         // flag de statut (attente ou traite une requete)
    QMutex mutex;
};

/** \class      ThreadPool
*   \authors    Adam Zouari et Oussama Lagha
*   \date       25 Mai 2018
*   \brief      Implementation du recyclage de threads
*/
class ThreadPool {

public:

    /**
    *   \brief          Constructeur de ThreadPool
    *   \param maxThreadCount Nombre de threads que le pool gère
    */
    ThreadPool(int maxThreadCount) : currentThreadCount(0), maxThreadCount(maxThreadCount){
        workers.reserve(maxThreadCount);
    }

    /**
    *   \brief          Creation/Recyclage d'un thread et delegation du travail au Worker
    *   \param request  La requete a traité
    */
    void start(Runnable* request){

        mutex.lock();
        int id = 0;
        // si il y a encore des threads disponible
        if(currentThreadCount < maxThreadCount){


            // on cree un thread worker en lui passant la requete
            Worker* worker = new Worker(request);

            // on l'ajoute dans la liste de worker
            workers.push_back(worker);

            // on incremente le nombre de threads utilisés
            currentThreadCount++;

            // et on lance le traitement
            workers.at(id)->start();

        }else if ((id = getIdOfWaitingWorker()) != -1){     // recyclage d'un thread

            workers.at(id)->setWork(request);

        } else{     // aucun thread libre

            // attend qu'un worker soit disponible pour lui attribuer une tache
            waitWorker.wait(&mutex);
            id = getIdOfWaitingWorker();
            workers.at(id)->setWork(request);

        }
        mutex.unlock();
    }

    int getIdOfWaitingWorker(){

        for(int i = 0; i < workers.size(); i++){
            if(!(workers.at(i)->getIsWorking())){
                return i;
            }
        }
        return -1;
    }

    /**
    *   \brief      Destructeur de threadPool
    */
    ~ThreadPool(){

        // Termine chaque thread proprement
        for(Worker* w : workers)
            w->requestInterruption();
     }

protected:

    int maxThreadCount,           // nombre max de thread possible dans le pool
    currentThreadCount;           // nombre de thread utilisé
    QVector<Worker*> workers;     // liste de worker
    QWaitCondition waitWorker;    // permet l'attente d'un worker
    QMutex mutex;                 // permet de proteger les sections critique

};

#endif // THREADPOOL_H
