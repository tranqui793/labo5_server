#ifndef PRODUCERCONSUMERBUFFER_H
#define PRODUCERCONSUMERBUFFER_H

#include "abstractbuffer.h"
#include "hoaremonitor.h"

/** \class      Producerconsumerbuffer
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      Implementation de l'interface AbstractBuffer<T>
*               afin de creer des tampons qui permetteront aux threads
*               de s'echanger des requetes et des reponses
*/
template <typename T>
class producerconsumerbuffer : public AbstractBuffer<T>,public HoareMonitor
{

public:

    /**
     * \brief constructeur du tampon
     * \param size taille maximal du tampon
     */
    producerconsumerbuffer(unsigned size):size(size){
        if((elements = new T[size]) != 0)
            head = tail = currentSize = 0;
    }

    /**
     * \brief ajout element au tampon
     * \param item Item a ajouter au tampon
     */
    void put(T item){
        monitorIn();
        if (currentSize == size)
            wait(notFull);
        currentSize += 1;
        elements[head] = item;
        head = (head + 1) % N;
        signal(notEmpty);
        monitorOut();
    }

    /**
     * \brief recupere un element du tampon
     */
    T get (){
        T item;
        monitorIn();
        if (size == 0) {
            wait(&notEmpty);
        }
        item = elements[tail];
        size -= 1;
        tail = (tail + 1) % size;
        signal(notFull);
        monitorOut();
        return item;
    }

protected:
    T *elements; //
    int head,tail,currentSize,size;//

    Condition notFull, notEmpty;  //

};

#endif // PRODUCERCONSUMERBUFFER_H
