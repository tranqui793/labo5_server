#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include <QThread>
class RequestHandler:public QThread
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;

public:
    RequestHandler(Request request,AbstractBuffer<Response>* responses, bool hasDebugLog):responses(responses), request(request), hasDebugLog(hasDebugLog) {}
    void run(){

    }
    Response handle();
};

#endif // REQUESTHANDLER_H
