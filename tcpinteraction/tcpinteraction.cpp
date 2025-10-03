#include "tcpinteraction.h"
#include <QDataStream>

TcpInteraction::TcpInteraction() {}

TcpInteraction::TcpInteraction(const QDateTime &dateTime,
                               const QHostAddress &hostAddress, quint64 port,
                               const QJsonObject &body)
    : m_dateTime(dateTime), m_hostAddress(hostAddress), m_port(port),
    m_body(body) {}

TcpInteraction::~TcpInteraction() {}

TcpInteraction TcpInteraction::fromJson(const QJsonObject &json) {
    TcpInteraction interaction;
    interaction.initFromJson(json);
    return interaction;
}

TcpInteraction TcpInteraction::fromSocket(QTcpSocket *socket) {
    TcpInteraction interaction;
    interaction.initFromSocket(socket);
    return interaction;
}

QJsonObject TcpInteraction::toJson() const {
    QJsonObject json;
    json["dateTime"] = m_dateTime.toString();
    json["hostAddress"] = m_hostAddress.toString();
    json["port"] = qint64(m_port);
    json["body"] = m_body;
    return json;
}

QByteArray TcpInteraction::toBytes() const {
    QByteArray bytes = QJsonDocument(toJson()).toJson();
    return valueToBytes(bytes.length()) + bytes;
}

void TcpInteraction::initFromJson(const QJsonObject &json) {
    m_dateTime = QDateTime::fromString(json["dateTime"].toString());
    m_hostAddress = QHostAddress(json["hostAddress"].toString());
    m_port = json["port"].toInteger();
    m_body = json["body"].toObject();
}

void TcpInteraction::initFromSocket(QTcpSocket *socket) {
    qint64 length = bytesToValue(socket->read(8));
    initFromJson(QJsonDocument::fromJson(socket->read(length)).object());
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

QDateTime TcpInteraction::dateTime() const { return m_dateTime; }

QHostAddress TcpInteraction::hostAddress() const { return m_hostAddress; }

quint64 TcpInteraction::port() const { return m_port; }

QJsonObject TcpInteraction::body() const { return m_body; }

bool TcpInteraction::isNull() const { return m_isNull; }
