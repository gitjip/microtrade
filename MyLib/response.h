#ifndef RESPONSE_H
#define RESPONSE_H

#include "mylib_constants.h"
#include "mylib_global.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

namespace My {
class MYLIB_EXPORT Response {
public:
    Response(int status, const Headers &headers, const Body &body,
             const QString &error);
    Response(const QJsonObject &object);
    operator QJsonObject() const;

public:
    int status;
    Headers headers;
    Body body;
    QString error;
};
} // namespace My

#endif // RESPONSE_H
