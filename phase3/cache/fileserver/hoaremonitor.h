#ifndef HOAREMONITOR_H
#define HOAREMONITOR_H


#include <QSemaphore>

/**
 * This class allows to easily create a monitor as defined by Hoare in 1974.
 * It offers functions that allow to define the entry point of the monitor
 * as well as condition variables and the functions needed to use them.
 * It is meant to be a superclass of an actual implementation, as presented
 * in the example.
 */
class HoareMonitor
{
protected:

    HoareMonitor(): monitorMutex(1), monitorSignale(0), monitorNbSignale(0) {}

    class Condition
    {
        friend HoareMonitor;

    public:
        Condition(): waitingSem(0), nbWaiting(0) {}

        // Test si il y des threads en attente sur la condition
        bool notEmpty(){return nbWaiting;}

    private:
        QSemaphore waitingSem;
        int nbWaiting;
    };

    /**
     * This function has to be called at the beginning of each function being
     * an entry point to the monitor.
     */
    void monitorIn(){

        monitorMutex.acquire();

    }

    /**
     * This function has to be called at the end of each function being
     * an entry point to the monitor.
     */
    void monitorOut(){

        if (monitorNbSignale > 0)
                monitorSignale.release();
            else
                monitorMutex.release();
    }

    /**
     * This function implements the waiting on a condition, as defined by Hoare.
     * When the thread is waken by a signal, it continues with the mutual
     * exclusion.
     */
    void wait(Condition &cond){
        cond.nbWaiting += 1;
           if (monitorNbSignale > 0)
               monitorSignale.release();
           else
               monitorMutex.release();
           cond.waitingSem.acquire();
           cond.nbWaiting -= 1;
    }

    /**
     * This function implements the signaling of a condition, as defined by
     * Hoare. If no thread is waiting for the condition, then nothing happens,
     * but if there is one the thread calling signal is suspended, waiting for
     * the other one to finish.
     */
    void signal(Condition &cond){
        if (cond.nbWaiting>0) {
                monitorNbSignale += 1;
                cond.waitingSem.release();
                monitorSignale.acquire();
                monitorNbSignale -= 1;
            }
    }

private:

    //! Mutex for the protecting the entire monitor
    QSemaphore monitorMutex;
    //! Blocking semaphore for the thread doing a signal(condition)
    QSemaphore monitorSignale;
    //! Number of threads waiting on the semaphore monitorSignale
    int monitorNbSignale;
};


#endif // HOAREMONITOR_H
