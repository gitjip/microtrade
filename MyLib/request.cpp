#include "request.h"

namespace My {
Request::Request(const QString &method, const QString &route,
                 const QJsonObject &headers, const QJsonValue &body)
    : method(method), route(route), headers(headers), body(body) {}

Request::Request(const QJsonObject &object)
    : method(object["method"].toString()), route(object["route"].toString()),
    headers(object["headers"].toObject()), body(object["body"]) {}

Request::operator QJsonObject() const {
    QJsonObject object;
    object["method"] = method;
    object["route"] = route;
    object["headers"] = headers;
    object["body"] = body;
    return object;
}
} // namespace My
