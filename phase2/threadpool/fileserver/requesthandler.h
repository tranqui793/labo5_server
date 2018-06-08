#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "runnable.h"
#include <QThread>

/** \class      RequestHandler
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      permet de traiter la requete et ajoute la réponse
*               dans le buffer responses
*/
class RequestHandler:public Runnable
{

public:
    RequestHandler(Request request,AbstractBuffer<Response>* responses, bool hasDebugLog):responses(responses), request(request), hasDebugLog(hasDebugLog) {}
    Response handle();
    void run(){

        //ajout dans le tampon de la response retourné par le handler
        responses->put(this->handle());
    }
    virtual QString id(){
        return ""+idRequest;
    }

private:
    int idRequest=0;
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};

#endif // REQUESTHANDLER_H
