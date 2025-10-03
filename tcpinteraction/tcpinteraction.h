#ifndef TCPINTERACTION_H
#define TCPINTERACTION_H

#include "tcpinteraction_global.h"
#include <QDateTime>
#include <QHostAddress>
#include <QJsonObject>
#include <QTcpSocket>

class TCPINTERACTION_EXPORT TcpInteraction {
public:
    TcpInteraction();
    TcpInteraction(const QDateTime &dateTime, const QHostAddress &hostAddress,
                   quint64 port, const QJsonObject &body = QJsonObject());
    virtual ~TcpInteraction();
    static TcpInteraction fromJson(const QJsonObject &json);
    // static TcpInteraction fromSocket(QTcpSocket *socket);
    virtual QJsonObject toJson() const;
    QByteArray toBytes() const;

public:
    QDateTime dateTime() const;
    QHostAddress hostAddress() const;
    quint64 port() const;
    QJsonObject body() const;
    bool isNull() const;

protected:
    virtual void initFromJson(const QJsonObject &json);
    // virtual void initFromSocket(QTcpSocket *socket);
    static QByteArray valueToBytes(qint64 value);
    static qint64 bytesToValue(QByteArray bytes);

protected:
    QDateTime m_dateTime = QDateTime::currentDateTime();
    QHostAddress m_hostAddress = QHostAddress::LocalHost;
    quint64 m_port = 0;
    QJsonObject m_body;
    bool m_isNull =true;
};

#endif // TCPINTERACTION_H
