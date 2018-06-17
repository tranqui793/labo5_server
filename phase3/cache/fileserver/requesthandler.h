#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "runnable.h"
#include "readerwritercache.h"
#include <QThread>

/** \class      RequestHandler
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 Mai 2018
*   \brief      Modification de la version de l'etape 1, maintenant herite de Runnable
*/
class RequestHandler : public Runnable
{

public:

    RequestHandler(Request request,AbstractBuffer<Response>* responses, bool hasDebugLog, ReaderWriterCache* cache)
        :responses(responses), request(request), hasDebugLog(hasDebugLog), cache(cache) {}
/**
*   \brief  permet de traiter la requete
*/
    Response handle();
/**
*   \brief  ajout de la reponse dans le tampon des reponses
*/
    void run(){

        Response resp;
        Option<Response> cachedResponse = cache->tryGetCachedResponse(request);
        if (cachedResponse.hasValue()) {
            resp = cachedResponse.value();
        } else {
            resp = this->handle();
            cache->putResponse(resp);
        }
        responses->put(resp);

    }
    /**
    *   \brief  retourne l'id du request en format QString
    */
    virtual QString id(){
        return ""+idRequest;
    }

private:
    int idRequest=0;
    Request request;
    AbstractBuffer<Response>* responses;
    ReaderWriterCache* cache;
    bool hasDebugLog;
};

#endif // REQUESTHANDLER_H
