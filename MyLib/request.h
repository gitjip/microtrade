#ifndef REQUEST_H
#define REQUEST_H

#include "mylib_global.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

namespace My {
class MYLIB_EXPORT Request {
public:
    Request(const QString &method, const QString &route,
            const QJsonObject &headers, const QJsonValue &body);
    Request(const QJsonObject &object);
    operator QJsonObject() const;

public:
    QString method;
    QString route;
    QJsonObject headers;
    QJsonValue body;
};
} // namespace My

#endif // REQUEST_H
