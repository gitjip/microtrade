#include "tcprequest.h"

TcpRequest::TcpRequest() {}

TcpRequest::TcpRequest(const QDateTime &dateTime,
                       const QHostAddress &hostAddress, quint64 port,
                       const QString &route, qint64 timeout,
                       const QJsonObject &body)
    : TcpInteraction(dateTime, hostAddress, port, body), m_route(route),
    m_timeout(timeout) {}

TcpRequest::TcpRequest(const QJsonObject &jsonObj)
    : TcpInteraction(QDateTime::fromString(jsonObj["dateTime"].toString()),
                     QHostAddress(jsonObj["hostAddress"].toString()),
                     jsonObj["port"].toInteger(), jsonObj["body"].toObject()),
    m_route(jsonObj["route"].toString()),
    m_timeout(jsonObj["timeout"].toInteger()) {}

TcpRequest::~TcpRequest() {}

TcpRequest::operator QJsonObject() const {
    return QJsonObject({{"dateTime", m_dateTime.toString()},
                        {"hostAddress", m_hostAddress.toString()},
                        {"port", qint64(m_port)},
                        {"body", m_body},
                        {"route", m_route},
                        {"timeout", m_timeout}});
}

TcpRequest TcpRequest::fromSocket(QTcpSocket *socket) {
    qint64 length = bytesToValue(socket->read(8));
    return TcpRequest(QJsonDocument::fromJson(socket->read(length)).object());
}

QString TcpRequest::route() const { return m_route; }

qint64 TcpRequest::timeout() const { return m_timeout; }
