#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>
/**
*   \brief          Constructeur de ReaderWriterCache
*
*/
ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    timer=new InvalidationTimer(this);
    timer->start();
}
/**
*   \brief          Destructeur
*/
ReaderWriterCache::~ReaderWriterCache()
{
    timer->requestInterruption();
    delete timer;
}
/**
*   \brief
*   \param response permet l'ajout au map
*/
void ReaderWriterCache::putResponse(Response &response) {
    lock.lockWriting();
        //pour chaque nouvelle requete on cree une struct avec le time courrant

    TimestampedResponse response_struct(response,timer->time);

    //l'ajout dans le cache
    //map prend string et TimestampedResponse donc on peut pas stockee la request instance on met le path
    map.insert(response.getRequest().getFilePath(),response_struct);

    lock.unlockWriting();
}
/**
*   \brief          permet de recuperer la resonse si elle exist
*   \param request  la requete pour la quelle on veut recupere la response
*/
Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {
    lock.lockReading();
    Option<Response> res = Option<Response>::none();

    //on essaye de recuperer l'element

   QHash<QString,TimestampedResponse>::const_iterator i= map.find(request.getFilePath());
    if(i !=map.end()){
        //si on a une response on met a jour le le timerstamp et on recupere la response
        res=Option<Response>::some(i.value());
        i.timestamp=timer->time;
    }


    lock.unlockReading();
    return res;
}
