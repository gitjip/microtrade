#ifndef TCPREQUEST_H
#define TCPREQUEST_H

#include "tcpinteraction_global.h"
#include "tcpinteraction.h"
#include <QTcpSocket>

class TCPINTERACTION_EXPORT TcpRequest : public TcpInteraction {
public:
    TcpRequest();
    TcpRequest(bool isValid, const QDateTime &dateTime,
               const QHostAddress &hostAddress, quint64 port,
               const QString &authorizedToken, const QString &route,
               qint64 timeout, const QJsonObject &body = QJsonObject());
    TcpRequest(const QJsonObject &jsonObj);
    ~TcpRequest() override;
    operator QJsonObject() const override;
    static TcpRequest fromSocket(QTcpSocket *socket);
    QString authorizedToken() const;
    QString route() const;
    qint64 timeout() const;

private:
    QString m_authorizedToken;
    QString m_route;
    qint64 m_timeout = -1; // -1 if timeout disabled
};

#endif // TCPREQUEST_H
