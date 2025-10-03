#include "tcprequest.h"

TcpRequest::TcpRequest() {}

TcpRequest::TcpRequest(const QDateTime &dateTime,
                       const QHostAddress &hostAddress, quint64 port,
                       const QString &route, qint64 timeout,
                       const QJsonObject &body)
    : TcpInteraction(dateTime, hostAddress, port, body), m_route(route),
    m_timeout(timeout) {}

TcpRequest::~TcpRequest() {}

TcpRequest TcpRequest::fromJson(const QJsonObject &json) {
    TcpRequest request;
    request.initFromJson(json);
    return request;
}

TcpRequest TcpRequest::fromSocket(QTcpSocket *socket) {
    qint64 length = bytesToValue(socket->read(8));
    return fromJson(QJsonDocument::fromJson(socket->read(length)).object());
}

QJsonObject TcpRequest::toJson() const {
    QJsonObject json = TcpInteraction::toJson();
    json["route"] = m_route;
    json["timeout"] = m_timeout;
    return json;
}

void TcpRequest::initFromJson(const QJsonObject &json) {
    TcpInteraction::initFromJson(json);
    m_route = json["route"].toString();
    m_timeout = json["timeout"].toInteger();
}

// void TcpRequest::initFromSocket(QTcpSocket *socket) {
//     qint64 length = bytesToValue(socket->read(8));
//     initFromJson(QJsonDocument::fromJson(socket->read(length)).object());
// }

QString TcpRequest::route() const { return m_route; }

qint64 TcpRequest::timeout() const { return m_timeout; }
