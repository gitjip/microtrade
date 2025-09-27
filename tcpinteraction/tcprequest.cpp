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
          jsonObj[toString(Attribute::IsValid)].toBool(),
          QDateTime::fromString(jsonObj[toString(Attribute::DateTime)].toString()),
          QHostAddress(jsonObj[toString(Attribute::HostAddress)].toString()),
          jsonObj[toString(Attribute::Port)].toInteger(),
          jsonObj[toString(Attribute::Body)].toObject()),
    m_authorizedToken(jsonObj[toString(Attribute::AuthorizedToken)].toString()),
    m_route(jsonObj[toString(Attribute::Route)].toString()),
    m_timeout(jsonObj[toString(Attribute::Timeout)].toInteger()) {}

TcpRequest::~TcpRequest() {}

TcpRequest::operator QJsonObject() const {
    return QJsonObject({{toString(Attribute::IsValid), m_isValid},
                        {toString(Attribute::DateTime), m_dateTime.toString()},
                        {toString(Attribute::HostAddress), m_hostAddress.toString()},
                        {toString(Attribute::Port), qint64(m_port)},
                        {toString(Attribute::Body), m_body},
                        {toString(Attribute::AuthorizedToken), m_authorizedToken},
                        {toString(Attribute::Route), m_route},
                        {toString(Attribute::Timeout), m_timeout}});
}

TcpRequest TcpRequest::fromSocket(QTcpSocket *socket) {
    qint64 length = toValue(socket->read(8));
    return TcpRequest(QJsonDocument::fromJson(socket->read(length)).object());
}

QString TcpRequest::authorizedToken() const { return m_authorizedToken; }

QString TcpRequest::route() const { return m_route; }

qint64 TcpRequest::timeout() const { return m_timeout; }
