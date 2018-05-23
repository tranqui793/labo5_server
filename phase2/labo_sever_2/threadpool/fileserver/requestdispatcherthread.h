#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QThread>
#include <QLinkedList>
#include "requesthandler.h"
#include "abstractbuffer.h"


class requestdispatcherthread:public QThread
{
public:
    requestdispatcherthread(AbstractBuffer<Request>* requests,AbstractBuffer<Response>* responses,bool hasDebugLog):hasDebugLog(hasDebugLog),responses(responses),requests(requests){

    }
    void run(){
        while(true){

            if(hasDebugLog)
                qDebug()<<"request processing starting";

            Request request = requests->get();
            RequestHandler* handler=new RequestHandler(request,responses,hasDebugLog);
            allHandlers.push_back(handler);
            handler->start();

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
