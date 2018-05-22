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
            RequestHandler* handler=new RequestHandler(requests->get(),responses,hasDebugLog);
            handler->start();
            allHandlers.push_back(handler);
            for(RequestHandler* e:allHandlers){
                if(e->isFinished())
                {
                    e->deleteLater();
                    allHandlers.removeOne(e);
                }
            }
            if(hasDebugLog)
                qDebug()<<"request processing";
        }
    }
private:
    QLinkedList<RequestHandler*> allHandlers;
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};
#endif // REQUESTDISPATCHERTHREAD_H
