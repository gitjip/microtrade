#include "tcprequest.h"

TcpRequest::TcpRequest() {}

TcpRequest::TcpRequest(bool isValid, const QDateTime &dateTime,
                       const QHostAddress &hostAddress, quint64 port,
                       const QString &authorizedToken, const QString &route,
                       qint64 timeout, const QJsonObject &body)
    : TcpInteraction(isValid, dateTime, hostAddress, port, body),
    m_authorizedToken(authorizedToken), m_route(route), m_timeout(timeout) {}

TcpRequest::TcpRequest(const QJsonObject &jsonObj)
    : TcpInteraction(
          jsonObj[attributeToString(Attribute::IsValid)].toBool(),
          QDateTime::fromString(jsonObj[attributeToString(Attribute::DateTime)].toString()),
          QHostAddress(jsonObj[attributeToString(Attribute::HostAddress)].toString()),
          jsonObj[attributeToString(Attribute::Port)].toInteger(),
          jsonObj[attributeToString(Attribute::Body)].toObject()),
    m_authorizedToken(jsonObj[attributeToString(Attribute::AuthorizedToken)].toString()),
    m_route(jsonObj[attributeToString(Attribute::Route)].toString()),
    m_timeout(jsonObj[attributeToString(Attribute::Timeout)].toInteger()) {}

TcpRequest::~TcpRequest() {}

TcpRequest::operator QJsonObject() const {
    return QJsonObject({{attributeToString(Attribute::IsValid), m_isValid},
                        {attributeToString(Attribute::DateTime), m_dateTime.toString()},
                        {attributeToString(Attribute::HostAddress), m_hostAddress.toString()},
                        {attributeToString(Attribute::Port), qint64(m_port)},
                        {attributeToString(Attribute::Body), m_body},
                        {attributeToString(Attribute::AuthorizedToken), m_authorizedToken},
                        {attributeToString(Attribute::Route), m_route},
                        {attributeToString(Attribute::Timeout), m_timeout}});
}

TcpRequest TcpRequest::fromSocket(QTcpSocket *socket) {
    qint64 length = toValue(socket->read(8));
    return TcpRequest(QJsonDocument::fromJson(socket->read(length)).object());
}

QString TcpRequest::authorizedToken() const { return m_authorizedToken; }

QString TcpRequest::route() const { return m_route; }

qint64 TcpRequest::timeout() const { return m_timeout; }
