#ifndef TCPINTERACTION_H
#define TCPINTERACTION_H

#include "tcpinteraction_global.h"
#include <QDateTime>
#include <QHostAddress>
#include <QJsonObject>

class TCPINTERACTION_EXPORT TcpInteraction {
public:
    TcpInteraction();
    TcpInteraction(const QDateTime &dateTime,
                   const QHostAddress &hostAddress, quint64 port,
                   const QJsonObject &body = QJsonObject());
    TcpInteraction(const QJsonObject &body);
    virtual ~TcpInteraction();
    virtual operator QJsonObject() const = 0;
    operator QByteArray() const;

public:
    bool isNull() const;
    QDateTime dateTime() const;
    QHostAddress hostAddress() const;
    quint64 port() const;
    QJsonObject body() const;

protected:
    static QByteArray valueToBytes(qint64 value);
    static qint64 bytesToValue(QByteArray bytes);

protected:
    bool m_isValid = false;
    QDateTime m_dateTime = QDateTime::currentDateTime();
    QHostAddress m_hostAddress = QHostAddress("127.0.0.1");
    quint64 m_port = 0;
    QJsonObject m_body;

};

#endif // TCPINTERACTION_H
