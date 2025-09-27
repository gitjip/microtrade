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
          jsonObj[toString(Attribute::IsValid)].toBool(),
          QDateTime::fromString(jsonObj[toString(Attribute::DateTime)].toString()),
          QHostAddress(jsonObj[toString(Attribute::HostAddress)].toString()),
          jsonObj[toString(Attribute::Port)].toInteger(),
          jsonObj[toString(Attribute::Body)].toObject()),
    m_success(jsonObj[toString(Attribute::Success)].toBool()),
    m_statusType(jsonObj[toString(Attribute::StatusType)].toString()),
    m_statusDetail(jsonObj[toString(Attribute::StatusDetail)].toString()) {}

TcpResponse::~TcpResponse() {}

TcpResponse::operator QJsonObject() const {
    return QJsonObject({{toString(Attribute::IsValid), m_isValid},
                        {toString(Attribute::DateTime), m_dateTime.toString()},
                        {toString(Attribute::HostAddress), m_hostAddress.toString()},
                        {toString(Attribute::Port), qint64(m_port)},
                        {toString(Attribute::Body), m_body},
                        {toString(Attribute::Success), m_success},
                        {toString(Attribute::StatusType), m_statusType},
                        {toString(Attribute::StatusDetail), m_statusDetail}});
}

TcpResponse TcpResponse::fromSocket(QTcpSocket *socket) {
    qint64 length = toValue(socket->read(8));
    return TcpResponse(QJsonDocument::fromJson(socket->read(length)).object());
}

bool TcpResponse::success() const { return m_success; }

QString TcpResponse::statusType() const { return m_statusType; }

QString TcpResponse::statusDetail() const { return m_statusDetail; }
