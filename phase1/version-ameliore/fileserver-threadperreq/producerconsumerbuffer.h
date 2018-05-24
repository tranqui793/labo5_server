#ifndef PRODUCERCONSUMERBUFFER_H
#define PRODUCERCONSUMERBUFFER_H

#include "QSemaphore"
#include "QQueue"
#include "abstractbuffer.h"

/** \class      Producerconsumerbuffer
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      Implementation de l'interface AbstractBuffer<T>
*               afin de creer des tampons qui permetteront aux threads
*               de s'echanger des requetes et des reponses
*/
template <typename T>
class producerconsumerbuffer : public AbstractBuffer<T>
{

public:

    producerconsumerbuffer(){
        // Pour autoriser l'arrivée d'une requete/reponse
        waitEmpty.release();
    }

    virtual void put(T item){
        waitEmpty.acquire();
        buffer.enqueue(item);
        waitFull.release();
    }

    virtual T get (){
        T item;
        waitFull.acquire();
        item = buffer.dequeue();
        waitEmpty.release();
        return item;
    }

protected:

    QQueue<T> buffer;
    QSemaphore waitEmpty, waitFull;
};

#endif // PRODUCERCONSUMERBUFFER_H
