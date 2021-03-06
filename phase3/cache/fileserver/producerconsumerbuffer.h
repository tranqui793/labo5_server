#ifndef PRODUCERCONSUMERBUFFER_H
#define PRODUCERCONSUMERBUFFER_H

#include "abstractbuffer.h"
#include <QQueue>

/** \class      Producerconsumerbuffer
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      Modification du buffer de l'etape 1 afin de gerer le nombre max de requetes dans le tampon
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

        waitEmpty.acquire();
        nbElements++;
        buffer.enqueue(item);
        waitFull.release();
    }

    /**
     * \brief  essaye d'ajouter un element au tampon
     * \param item element a ajouter
     */
    virtual bool tryPut(T item){
        bool res = false;
        mutex.acquire();

        if (nbElements < bufferSize) {       //si le tampon est plein on sort sans rien faire
            put(item);
            res = true;
        }
        mutex.release();
        return res;
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


protected:
    QQueue<T> buffer;           //tampon des elements
    int nbElements,             //nombre d'element dans le tampon(taille courant du tampon)
    bufferSize;                 //taille max du tampon
   QSemaphore waitEmpty,        //permet d'attendre son tour pour ajouter dans le tampon
   waitFull,                    //permet d'attendre si le tampon est vide
   mutex;                       //permet de protégé e la section critique
};

#endif // PRODUCERCONSUMERBUFFER_H
