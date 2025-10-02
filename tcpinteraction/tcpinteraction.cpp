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

QString TcpInteraction::attributeToString(Attribute data) {
    switch (data) {
    case Attribute::IsValid:
        return "is_valid";
    case Attribute::DateTime:
        return "date_time";
    case Attribute::Body:
        return "body";
    case Attribute::HostAddress:
        return "host_address";
    case Attribute::Port:
        return "port";
    case Attribute::Authorization:
        return "authorized_token";
    case Attribute::Route:
        return "route";
    case Attribute::Timeout:
        return "timeout";
    case Attribute::Success:
        return "success";
    case Attribute::StatusType:
        return "status_type";
    case Attribute::StatusDetail:
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
