#include "tcpresponse.h"
#include <QString>

TcpResponse::TcpResponse() {}

TcpResponse::TcpResponse(const QDateTime &dateTime,
                         const QHostAddress &hostAddress, quint64 port,
                         bool success, StatusType statusType,
                         const QString &statusDetail, const QJsonObject &body)
    : TcpInteraction(dateTime, hostAddress, port, body), m_success(success),
    m_statusType(statusType), m_statusDetail(statusDetail) {}

TcpResponse::TcpResponse(const QJsonObject &jsonObj)
    : TcpInteraction(QDateTime::fromString(jsonObj["dateTime"].toString()),
                     QHostAddress(jsonObj["hostAddress"].toString()),
                     jsonObj["port"].toInteger(), jsonObj["body"].toObject()),
    m_success(jsonObj["success"].toBool()),
    m_statusType(stringToStatusType(jsonObj["statusType"].toString())),
    m_statusDetail(jsonObj["statusDetail"].toString()) {}

TcpResponse::~TcpResponse() {}

TcpResponse::operator QJsonObject() const {
    return QJsonObject({{"dateTime", m_dateTime.toString()},
                        {"hostAddress", m_hostAddress.toString()},
                        {"port", qint64(m_port)},
                        {"body", m_body},
                        {"success", m_success},
                        {"statusType", statusTypeToString(m_statusType)},
                        {"statusDetail", m_statusDetail}});
}

TcpResponse TcpResponse::fromSocket(QTcpSocket *socket) {
    qint64 length = bytesToValue(socket->read(8));
    return TcpResponse(QJsonDocument::fromJson(socket->read(length)).object());
}

QString TcpResponse::statusTypeToString(StatusType statusType) {
    switch (statusType) {
    case StatusType::Success:
        return "success";
    case StatusType::NotFound:
        return "notFound";
    case StatusType::Failed:
        return "failed";
    case StatusType::Unauthorized:
        return "unauthorized";
    case StatusType::RuntimeError:
        return "runtimeError";
    case StatusType::Timeout:
        return "timeout";
    case StatusType::InvalidRequest:
        return "invalidStatus";
    default:
        return "";
    }
}

TcpResponse::StatusType
TcpResponse::stringToStatusType(const QString &statusTypeString) {
    if (statusTypeString == "success") {
        return StatusType::Success;
    } else if (statusTypeString == "notFound") {
        return StatusType::NotFound;
    } else if (statusTypeString == "failed") {
        return StatusType::Failed;
    } else if (statusTypeString == "unauthorized") {
        return StatusType::Unauthorized;
    } else if (statusTypeString == "runtimeError") {
        return StatusType::RuntimeError;
    } else if (statusTypeString == "timeout") {
        return StatusType::Timeout;
    } else if (statusTypeString == "invalidStatus") {
        return StatusType::InvalidRequest;
    } else {
        return StatusType::InvalidRequest; // default
    }
}

bool TcpResponse::success() const { return m_success; }

TcpResponse::StatusType TcpResponse::statusType() const { return m_statusType; }

QString TcpResponse::statusDetail() const { return m_statusDetail; }
