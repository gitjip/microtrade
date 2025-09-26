#include "tcpresponse.h"
#include <QString>

TcpResponse::TcpResponse() {}

TcpResponse::TcpResponse(bool isValid, const QDateTime &dateTime,
                         const QHostAddress &hostAddress, quint64 port,
                         bool success, const QString &statusDetail,
                         const QString &statusType, const QJsonObject &body)
    : TcpInteraction(isValid, dateTime, hostAddress, port, body),
    m_success(success), m_statusType(statusType),
    m_statusDetail(statusDetail) {}

TcpResponse::TcpResponse(const QJsonObject &jsonObj)
    : TcpInteraction(
          jsonObj[toString(IsValid)].toBool(),
          QDateTime::fromString(jsonObj[toString(DateTime)].toString()),
          QHostAddress(jsonObj[toString(HostAddress)].toString()),
          jsonObj[toString(Port)].toInteger(),
          jsonObj[toString(Body)].toObject()),
    m_success(jsonObj[toString(Success)].toBool()),
    m_statusType(jsonObj[toString(StatusType)].toString()),
    m_statusDetail(jsonObj[toString(StatusDetail)].toString()) {}

TcpResponse::~TcpResponse() {}

TcpResponse::operator QJsonObject() const {
    return QJsonObject({{toString(IsValid), m_isValid},
                        {toString(DateTime), m_dateTime.toString()},
                        {toString(HostAddress), m_hostAddress.toString()},
                        {toString(Port), qint64(m_port)},
                        {toString(Body), m_body},
                        {toString(Success), m_success},
                        {toString(StatusType), m_statusType},
                        {toString(StatusDetail), m_statusDetail}});
}

bool TcpResponse::success() const { return m_success; }
QString TcpResponse::statusType() const { return m_statusType; }

QString TcpResponse::statusDetail() const { return m_statusDetail; }
