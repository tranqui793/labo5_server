#ifndef PRODUCERCONSUMERBUFFER_H
#define PRODUCERCONSUMERBUFFER_H

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

    /**
     * \brief constructeur du tampon
     * \param size taille maximal du tampon
     */
    producerconsumerbuffer(unsigned size){
        mutex.release();
        nbElements = 0;
        nbWaitingConso = 0;
        bufferSize = size;
    }

    /**
     * \brief ajout element au tampon
     * \param item Item a ajouter au tampon
     */
    virtual ~producerconsumerbuffer(){}
    virtual void put(T item){
        mutex.acquire();
        if (nbElements == bufferSize) { //si le tampon et plein on libére la mutex
            mutex.release();
            return;
        }
        //si le tampon n'est pas plein on ajoute au tampon et on réveil un consomateur en attente
        buffer.enqueue(item);
        nbElements ++;
        if (nbWaitingConso > 0) {
            nbWaitingConso -= 1;
            waitConso.release();
        }
        else {
            mutex.release();
        }
    }

    /**
     * \brief recupere un element du tampon
     */
    virtual T get (){
        T item;
        mutex.acquire();
        if (nbElements == 0) {  //si le tampon est vide les consomateurs doivent attendre
            nbWaitingConso += 1;
            mutex.release();
            waitConso.acquire();
            item=buffer.dequeue;
            nbElements --;
        }
        else {  //dans le cas ou le tampon contient des elements
            item=buffer.dequeue;
            nbElements --;
            mutex.release();
        }
        return item;
    }

protected:
    QQueue<T> buffer;   //tampon des elements
    int nbElements,     //nombre d'element dans le tampon(taille courant du tampon)
    bufferSize; //taille max du tampon
    QSemaphore mutex,   //permet de protégé la section critique
    waitConso;  //permet d'attendre si le tampon est vide
    unsigned nbWaitingConso;    //nombre de consomateurs en attente
};

#endif // PRODUCERCONSUMERBUFFER_H
