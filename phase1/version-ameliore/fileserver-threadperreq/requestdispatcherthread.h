#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QLinkedList>
#include "requesthandler.h"
#include "abstractbuffer.h"

/** \class      requestdispatcherthread
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      pour chaque request dans le buffer
*               on lance un requestHandler qui va s'occuper
*               de traiter le request
*/
class requestdispatcherthread : public QThread
{

public:
    requestdispatcherthread(AbstractBuffer<Request>* requests,AbstractBuffer<Response>* responses,bool hasDebugLog)
        : hasDebugLog(hasDebugLog),responses(responses),requests(requests){
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
    }

    void run(){

        while(true){

            if (hasDebugLog)
                qDebug() << "Waiting for request...";

            //on récupére la premiere requete dans le tampon
            Request request = requests->get();

            if (hasDebugLog)
                qDebug() << "Got a request " << request.getFilePath();

            RequestHandler* handler = new RequestHandler(request,responses,hasDebugLog);

            // on ajoute chaque handler dans une liste
            allHandlers.push_back(handler);

            // lancement du traitement de la request dans un thread dédié
            handler->start();

            // on parcours la liste des thread handlers qui tourne
            for(RequestHandler* e : allHandlers){

                // si il a terminé son execution
                if(e->isFinished())
                {
                     // on le supprime de la liste
                    allHandlers.removeOne(e);

                    // et on le detruit
                    delete(e);
                    break;
                }
            }
        }
    }
private:
    QLinkedList<RequestHandler*> allHandlers;
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};
#endif // REQUESTDISPATCHERTHREAD_H
