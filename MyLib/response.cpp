#include "response.h"

namespace My {
Response::Response(int status, const QJsonObject &headers,
                   const QJsonValue &body, const QString &error)
    : status(status), headers(headers), body(body), error(error) {}

Response::Response(const QJsonObject &object)
    : status(object["status"].toInt()), headers(object["headers"].toObject()),
    body(object["body"]), error(object["error"].toString()) {}

Response::operator QJsonObject() const {
    QJsonObject object;
    object["status"] = status;
    object["headers"] = headers;
    object["body"] = body;
    object["error"] = error;
    return object;
}
} // namespace My
