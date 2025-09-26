#include "tcpinteraction.h"
#include <QDataStream>

TcpInteraction::TcpInteraction() {}

TcpInteraction::TcpInteraction(bool isValid, const QDateTime &dateTime,
                               const QHostAddress &hostAddress, quint64 port,
                               const QJsonObject &body)
    : m_isValid(isValid), m_dateTime(dateTime), m_hostAddress(hostAddress),
    m_port(port), m_body(body) {}

TcpInteraction::~TcpInteraction() {}

TcpInteraction::operator QByteArray() const {
    QByteArray bytes = QJsonDocument(*this).toJson();
    return toFixedBytes(bytes.length()) + bytes;
}

QString TcpInteraction::toString(Item data) {
    switch (data) {
    case Item::IsValid:
        return "is_valid";
    case Item::DateTime:
        return "date_time";
    case Item::Body:
        return "body";
    case Item::HostAddress:
        return "host_address";
    case Item::Port:
        return "port";
    case Item::AuthorizedToken:
        return "authorized_token";
    case Item::Route:
        return "route";
    case Item::Timeout:
        return "timeout";
    case Item::Success:
        return "success";
    case Item::StatusType:
        return "status_type";
    case Item::StatusDetail:
        return "status_detail";
    default:
        return "";
    }
}

QByteArray TcpInteraction::toFixedBytes(qint64 value) {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << value;
    return bytes;
}

qint64 TcpInteraction::toValue(QByteArray bytes) {
    qint64 value;
    QDataStream stream(&bytes, QIODevice::ReadOnly);
    stream >> value;
    return value;
}

bool TcpInteraction::isValid() const { return m_isValid; }

QDateTime TcpInteraction::dateTime() const { return m_dateTime; }

QHostAddress TcpInteraction::hostAddress() const { return m_hostAddress; }

quint64 TcpInteraction::port() const { return m_port; }

QJsonObject TcpInteraction::body() const { return m_body; }
