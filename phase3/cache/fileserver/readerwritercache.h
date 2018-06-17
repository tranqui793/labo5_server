#ifndef READERWRITERCACHE_H
#define READERWRITERCACHE_H
#include <QHash>
#include <QThread>
#include <QMutex>
#include "option.h"
#include "request.h"
#include "response.h"
#include "readerwriterlock.h"


/** \class      rederwritercache
*   \authors    Adam Zouari et Oussama Lagha
*   \date       15 juin 2018
*   \brief      modification du readerwritercache afin de pouvoir ajouter et recupere des responses
*/
class ReaderWriterCache
{
private:
	struct TimestampedResponse {
		Response response;
        long timestamp;
     /**
    *   \brief              Constructeur de struct TimestampedResponse
    *   \param res          response enregistre la map
    *   \param timestamp    l'heure de la derniere utilisation
    */
        TimestampedResponse(Response res,long timestamp):response(res),timestamp(timestamp){}
	};

	class InvalidationTimer: public QThread {
		friend ReaderWriterCache;

	private:
        ReaderWriterCache* cache;

	public:
        InvalidationTimer(ReaderWriterCache* cache): cache(cache),time(0) {}
        unsigned time;          //represente le time courrant

	protected:
		void run() {

            while(true){
                QHash<QString, TimestampedResponse>::iterator iterator;       //iterator pour map
                for(iterator = cache->map.begin(); iterator != cache->map.end(); ){
                    struct TimestampedResponse value = iterator.value();

                    if((time - value.timestamp) < cache->staleDelaySec){            //si on a pas depasser le delai on verifie le suivant
                        iterator++;
                    }else{
                       iterator = cache->map.erase(iterator);                       //sinon on efface
                    }
                }

                QThread::sleep(cache->invalidationDelaySec);
                time += cache->invalidationDelaySec;
            }
		}
	};

    QHash<QString, TimestampedResponse> map;    //sert a enregistrer les response
    int invalidationDelaySec;       //interval entre deux verification
    int staleDelaySec;              //temps de validité
    InvalidationTimer* timer;       //timer pour la validation
    ReaderWriterLock lock;          //gére tout les priorité de reader et writer

public:
	ReaderWriterCache(int invalidationDelaySec, int staleDelaySec);
    ~ReaderWriterCache();

	Option<Response> tryGetCachedResponse(Request& request);
	void putResponse(Response& response);
};

#endif // READERWRITERCACHE_H
