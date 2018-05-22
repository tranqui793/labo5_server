#ifndef REQUEST_H
#define REQUEST_H
#include <QString>
#include"abstractbuffer.h"

class Request : public AbstractBuffer<Request>
{
private:
    QString filePath;
    QString clientId;

public:
    Request() {}
    Request(QString filePath, QString clientId): filePath(filePath), clientId(clientId) {}

    QString getFilePath() {
        return filePath;
    }

    QString getClientId() {
        return clientId;
    }

    void put(Request item){

    }
    Request get(){

    }


};

#endif // REQUEST_H
