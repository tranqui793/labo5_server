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
class requestdispatcherthread:public QThread
{
public:
    requestdispatcherthread(AbstractBuffer<Request>* requests,AbstractBuffer<Response>* responses,bool hasDebugLog):hasDebugLog(hasDebugLog),responses(responses),requests(requests){

    }
    void run(){
        while(true){

            if(hasDebugLog)
                qDebug()<<"request processing starting";

            Request request = requests->get();//on récupére le premier request sur la list
            RequestHandler* handler=new RequestHandler(request,responses,hasDebugLog);
            allHandlers.push_back(handler);
            handler->start();//lancement du traitement de la request
            //on cherche le handler fini et on le supprime de la list de tout
            //les handler en cours d'execution
            for(RequestHandler* e:allHandlers){
                if(e->isFinished())
                {
                    allHandlers.removeOne(e);
                    delete(e);
                }
            }

            if(hasDebugLog)
                qDebug()<<"request processing finished";
        }
    }
private:
    QLinkedList<RequestHandler*> allHandlers;
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};
#endif // REQUESTDISPATCHERTHREAD_H
