#include "tcpresponse.h"
#include <QString>

TcpResponse::TcpResponse() {}

TcpResponse::TcpResponse(qint64 contentLength, const QDateTime &dateTime,
                         const QHostAddress &hostAddress, quint64 port,
                         bool success, const QString &statusDetail,
                         const QString &statusType, const QJsonObject &body)
    : TcpInteraction(contentLength, dateTime, hostAddress, port, body),
    m_success(success), m_statusType(statusType),
    m_statusDetail(statusDetail) {}

TcpResponse::TcpResponse(const QJsonObject &jsonObj)
    : TcpInteraction(
          jsonObj[toString(ContentLength)].toInteger(),
          QDateTime::fromString(jsonObj[toString(DateTime)].toString()),
          QHostAddress(jsonObj[toString(HostAddress)].toString()),
          jsonObj[toString(Port)].toString().toULongLong(),
          jsonObj[toString(Body)].toObject()),
    m_success(jsonObj[toString(Success)].toBool()),
    m_statusType(jsonObj[toString(StatusType)].toString()),
    m_statusDetail(jsonObj[toString(StatusDetail)].toString()) {}

TcpResponse::~TcpResponse() {}

TcpResponse::operator QJsonObject() const
{
    return QJsonObject({{toString(ContentLength), m_contentLength},
                        {toString(DateTime), m_dateTime.toString()},
                        {toString(HostAddress), m_hostAddress.toString()},
                        {toString(Port), QString::number(m_port)},
                        {toString(Body), m_body},
                        {toString(Success), m_success},
                        {toString(StatusType), m_statusType},
                        {toString(StatusDetail), m_statusDetail}});
}
