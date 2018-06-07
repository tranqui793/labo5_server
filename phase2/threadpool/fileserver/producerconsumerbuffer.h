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
        mutex.release(size);
        waitEmpty.release(size);
        nbElements = 0;
        bufferSize = size;
    }
    /**
     * \brief destructeur
     */
    virtual ~producerconsumerbuffer(){}
    /**
     * \brief ajout element au tampon
     * \param item Item a ajouter au tampon
     */
    virtual void put(T item){

        mutex.acquire();
        if (nbElements==bufferSize) {       //si le tampon est plein on sort sans rien faire
            mutex.release();
            return;
        }
        waitEmpty.acquire();
        nbElements++;
        buffer.enqueue(item);
        mutex.release();
        waitFull.release();

=======
    void put(T item){
        monitorIn();
        if (currentSize == size)
            wait(notFull);
        currentSize += 1;
        elements[head] = item;
        head = (head + 1) % size;
        signal(notEmpty);
        monitorOut();
>>>>>>> Stashed changes
    }

    /**
     * \brief recupere un element du tampon
     */
    virtual T get (){

        T item;
        waitFull.acquire();
        nbElements--;
        item = buffer.dequeue();
        waitEmpty.release();
        return item;
    }

    bool tryPut(T item){
<<<<<<< Updated upstream
=======

    }

protected:
    T *elements; //
    int head,tail,currentSize,size;//
>>>>>>> Stashed changes

    }

protected:
    QQueue<T> buffer;           //tampon des elements
    int nbElements,             //nombre d'element dans le tampon(taille courant du tampon)
    bufferSize;                 //taille max du tampon
   QSemaphore waitEmpty,        //permet d'attendre son tour pour ajouter dans le tampon
   waitFull,                    //permet d'attendre si le tampon est vide
   mutex;                       //permet de protégé e la section critique
};

#endif // PRODUCERCONSUMERBUFFER_H
