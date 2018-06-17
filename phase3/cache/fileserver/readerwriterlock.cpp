#include "readerwriterlock.h"

/**
*   \brief          Constructeur de ReaderWriterLock
*/
ReaderWriterLock::ReaderWriterLock() : nbReaders(0) , isWriting(false){}

/**
*   \brief          Verrouillage pour effectuer une lecture
*/
void ReaderWriterLock::lockReading() {

    monitorIn();

    // Si on est deja entrain d'ecrire, on attend
    if(isWriting || notReading.notEmpty()){
        wait(notWriting);
    }
    signal(notWriting);

    monitorOut();
}

/**
*   \brief          Deverrouillage apres une lecture
*/
void ReaderWriterLock::unlockReading() {

    monitorIn();
    nbReaders--;

    // Si aucune lecture en cours le on signale aux writers
    if(nbReaders == 0){
        signal(notReading);
    }

    monitorOut();
}

/**
*   \brief          Verrouillage pour effectuer une ecriture
*/
void ReaderWriterLock::lockWriting() {

    monitorIn();

    // S'il y a deja des readers ou si on ecrit deja alors on attend que personne lise
    if(nbReaders > 0 || isWriting){
        wait(notReading);
    }

    isWriting = true;

    monitorOut();
}

/**
*   \brief          Deverrouillage apres une ecriture
*/
void ReaderWriterLock::unlockWriting() {
    
    monitorIn();

    isWriting = false;

    // Si on attend pour ecrire alors on le signal
    if(notReading.notEmpty()){
        signal(notReading);

    }else{ // Sinon on signal qu'on peut ecrire
        signal(notWriting);
    }

    monitorOut();
}
