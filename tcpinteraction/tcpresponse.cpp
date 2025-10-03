#include "tcpresponse.h"
#include <QString>

TcpResponse::TcpResponse() {}

TcpResponse::TcpResponse(bool success, StatusType statusType,
                         const QString &statusDetail, const QDateTime &dateTime,
                         const QHostAddress &hostAddress, quint64 port,
                         const QJsonObject &body)
    : TcpInteraction(dateTime, hostAddress, port, body), m_success(success),
    m_statusType(statusType), m_statusDetail(statusDetail) {}

TcpResponse::~TcpResponse() {}

TcpResponse TcpResponse::fromJson(const QJsonObject &json) {
    TcpResponse response;
    response.initFromJson(json);
    return response;
}

TcpResponse TcpResponse::fromSocket(QTcpSocket *socket) {
    qint64 length = bytesToValue(socket->read(8));
    return fromJson(QJsonDocument::fromJson(socket->read(length)).object());
}

QJsonObject TcpResponse::toJson() const {
    QJsonObject json = TcpInteraction::toJson();
    json["success"] = m_success;
    json["statusType"] = statusTypeToString(m_statusType);
    json["statusDetail"] = m_statusDetail;
    return json;
}

void TcpResponse::initFromJson(const QJsonObject &json) {
    TcpInteraction::initFromJson(json);
    m_success = json["success"].toBool();
    m_statusType = stringToStatusType(json["statusType"].toString());
    m_statusDetail = json["statusDetail"].toString();
}

// void TcpResponse::initFromSocket(QTcpSocket *socket) {
//     qint64 length = bytesToValue(socket->read(8));
//     initFromJson(QJsonDocument::fromJson(socket->read(length)).object());
// }

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
