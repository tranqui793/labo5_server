#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include <QThread>

/** \class      RequestHandler
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      permetde traiter le request et envoi la réponse
*               au buffer responses
*/
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
