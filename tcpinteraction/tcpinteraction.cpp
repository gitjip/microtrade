#include "tcpinteraction.h"
#include <QDataStream>

TcpInteraction::TcpInteraction() {}

TcpInteraction::TcpInteraction(const QDateTime &dateTime,
                               const QHostAddress &hostAddress, quint64 port,
                               const QJsonObject &body)
    : m_isValid(true), m_dateTime(dateTime), m_hostAddress(hostAddress),
    m_port(port), m_body(body) {}

TcpInteraction::~TcpInteraction() {}

TcpInteraction::operator QByteArray() const {
    QByteArray bytes = QJsonDocument(*this).toJson();
    return valueToBytes(bytes.length()) + bytes;
}

QByteArray TcpInteraction::valueToBytes(qint64 value) {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << value;
    return bytes;
}

qint64 TcpInteraction::bytesToValue(QByteArray bytes) {
    qint64 value;
    QDataStream stream(&bytes, QIODevice::ReadOnly);
    stream >> value;
    return value;
}

bool TcpInteraction::isNull() const { return m_isValid; }

QDateTime TcpInteraction::dateTime() const { return m_dateTime; }

QHostAddress TcpInteraction::hostAddress() const { return m_hostAddress; }

quint64 TcpInteraction::port() const { return m_port; }

QJsonObject TcpInteraction::body() const { return m_body; }
