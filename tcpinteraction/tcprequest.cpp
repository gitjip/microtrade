#include "tcprequest.h"

TcpRequest::TcpRequest() {}

TcpRequest::TcpRequest(qint64 contentLength, const QDateTime &dateTime,
                       const QHostAddress &hostAddress, quint64 port,
                       const QString &authorizedToken, const QString &route,
                       qint64 timeout, const QJsonObject &body)
    : TcpInteraction(contentLength, dateTime, hostAddress, port, body),
    m_authorizedToken(authorizedToken), m_route(route), m_timeout(timeout) {}

TcpRequest::TcpRequest(const QJsonObject &jsonObj)
    : TcpInteraction(
          jsonObj[toString(ContentLength)].toInteger(),
          QDateTime::fromString(jsonObj[toString(DateTime)].toString()),
          QHostAddress(jsonObj[toString(HostAddress)].toString()),
          jsonObj[toString(Port)].toString().toULongLong(),
          jsonObj[toString(Body)].toObject()),
    m_authorizedToken(jsonObj[toString(AuthorizedToken)].toString()),
    m_route(jsonObj[toString(Route)].toString()),
    m_timeout(jsonObj[toString(Timeout)].toInteger()) {}

TcpRequest::~TcpRequest() {}

TcpRequest::operator QJsonObject() const
{
    return QJsonObject({{toString(ContentLength), m_contentLength},
                        {toString(DateTime), m_dateTime.toString()},
                        {toString(HostAddress), m_hostAddress.toString()},
                        {toString(Port), QString::number(m_port)},
                        {toString(Body), m_body},
                        {toString(AuthorizedToken), m_authorizedToken},
                        {toString(Route), m_route},
                        {toString(Timeout), m_timeout}});
}
