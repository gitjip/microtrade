#include "tcpresponse.h"
#include <QString>

TcpResponse::TcpResponse() {}

TcpResponse::TcpResponse(bool isValid, const QDateTime &dateTime,
                         const QHostAddress &hostAddress, quint64 port,
                         bool success, StatusType statusType, const QString &statusDetail,
                         const QJsonObject &body)
    : TcpInteraction(isValid, dateTime, hostAddress, port, body),
    m_success(success), m_statusType(statusType),
    m_statusDetail(statusDetail) {}

TcpResponse::TcpResponse(const QJsonObject &jsonObj)
    : TcpInteraction(
          jsonObj[attributeToString(Attribute::IsValid)].toBool(),
          QDateTime::fromString(
              jsonObj[attributeToString(Attribute::DateTime)].toString()),
          QHostAddress(
              jsonObj[attributeToString(Attribute::HostAddress)].toString()),
          jsonObj[attributeToString(Attribute::Port)].toInteger(),
          jsonObj[attributeToString(Attribute::Body)].toObject()),
    m_success(jsonObj[attributeToString(Attribute::Success)].toBool()),
    m_statusType(
          stringToStatusType(jsonObj[attributeToString(Attribute::StatusType)].toString())),
    m_statusDetail(
          jsonObj[attributeToString(Attribute::StatusDetail)].toString()) {}

TcpResponse::~TcpResponse() {}

TcpResponse::operator QJsonObject() const {
    return QJsonObject(
        {{attributeToString(Attribute::IsValid), m_isValid},
         {attributeToString(Attribute::DateTime), m_dateTime.toString()},
         {attributeToString(Attribute::HostAddress), m_hostAddress.toString()},
         {attributeToString(Attribute::Port), qint64(m_port)},
         {attributeToString(Attribute::Body), m_body},
         {attributeToString(Attribute::Success), m_success},
         {attributeToString(Attribute::StatusType), statusTypeToString(m_statusType)},
         {attributeToString(Attribute::StatusDetail), m_statusDetail}});
}

TcpResponse TcpResponse::fromSocket(QTcpSocket *socket) {
    qint64 length = toValue(socket->read(8));
    return TcpResponse(QJsonDocument::fromJson(socket->read(length)).object());
}

QString TcpResponse::statusTypeToString(StatusType statusType) {
    switch (statusType) {
    case StatusType::Success:
        return "success";
    case StatusType::NotFound:
        return "not_found";
    case StatusType::Failed:
        return "failed";
    case StatusType::Unauthorized:
        return "unauthorized";
    case StatusType::RuntimeError:
        return "runtime_error";
    case StatusType::Timeout:
        return "timeout";
    case StatusType::InvalidRequest:
        return "invalid_status";
    default:
        return "";
    }
}

TcpResponse::StatusType
TcpResponse::stringToStatusType(const QString &statusTypeString) {
    if (statusTypeString == "success") {
        return StatusType::Success;
    } else if (statusTypeString == "not_found") {
        return StatusType::NotFound;
    } else if (statusTypeString == "failed") {
        return StatusType::Failed;
    } else if (statusTypeString == "unauthorized") {
        return StatusType::Unauthorized;
    } else if (statusTypeString == "runtime_error") {
        return StatusType::RuntimeError;
    } else if (statusTypeString == "timeout") {
        return StatusType::Timeout;
    } else if (statusTypeString == "invalid_status") {
        return StatusType::InvalidRequest;
    } else {
        return StatusType::InvalidRequest;   // default
    }
}

bool TcpResponse::success() const { return m_success; }

TcpResponse::StatusType TcpResponse::statusType() const { return m_statusType; }

QString TcpResponse::statusDetail() const { return m_statusDetail; }
