#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include "hoaremonitor.h"

/**
*   \class          ReaderWriterLock qui implemente les methode utile
*                   au mecanisme de Lecteur Rédacteur avec priorité
*                   aux lecteurs si lecture en cours
*/
class ReaderWriterLock : public HoareMonitor
{

public:
    ReaderWriterLock();

    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();

private:

    Condition notReading, notWriting;   // condition pour l'attente ne ecriture/lecture
    int nbReaders;                      // variable pour stocker le nombre de lecteurs
    bool isWriting;                     // flag pour savoir si on est entrain d'ecrire
};

#endif // READERWRITERLOCK_H
