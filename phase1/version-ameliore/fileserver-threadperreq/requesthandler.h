#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"

#include <QThread>
class RequestHandler:public QThread
{

public:
    RequestHandler(Request request,AbstractBuffer<Response>* responses, bool hasDebugLog):responses(responses), request(request), hasDebugLog(hasDebugLog) {}
    void run(){
        responses->put(this->handle());
    }
    Response handle();

private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};

#endif // REQUESTHANDLER_H
