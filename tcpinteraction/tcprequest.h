#ifndef TCPREQUEST_H
#define TCPREQUEST_H

#include "tcpinteraction.h"
#include "tcpinteraction_global.h"
#include <QTcpSocket>

class TCPINTERACTION_EXPORT TcpRequest : public TcpInteraction {
public:
    TcpRequest();
    TcpRequest(const QDateTime &dateTime, const QHostAddress &hostAddress,
               quint64 port, const QString &route, qint64 timeout,
               const QJsonObject &body = QJsonObject());
    ~TcpRequest() override;
    static TcpRequest fromJson(const QJsonObject &json);
    static TcpRequest fromSocket(QTcpSocket *socket);
    QJsonObject toJson() const override;

public:
    QString route() const;
    qint64 timeout() const;

private:
    void initFromJson(const QJsonObject &json) override;
    // void initFromSocket(QTcpSocket *socket) override;

private:
    QString m_route;
    qint64 m_timeout = -1; // -1 if timeout disabled
};

#endif // TCPREQUEST_H
