#ifndef RESPONSE_H
#define RESPONSE_H

#include <QJsonObject>
#include <QJsonDocument>
#include "request.h"
#include "abstractbuffer.h"

class Response : public AbstractBuffer <Response>{
private:
    Request request;
    QString response;

public:
    Response(){}
    Response(Request request, QString response):
        request(request), response(response) {}

    QString toJson() {
        QJsonObject obj;
        obj["request"] = request.getFilePath();
        obj["response"] = response;
        QJsonDocument doc(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        return strJson;
    }

    Request getRequest() {
        return request;
    }

    QString getResponse() {
        return response;
    }

    void put(Response item){

    }
    Response get(){

    }


};
#endif // RESPONSE_H
