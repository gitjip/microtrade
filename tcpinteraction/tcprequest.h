#ifndef TCPREQUEST_H
#define TCPREQUEST_H

#include "tcpinteraction.h"

class TcpRequest : public TcpInteraction
{
public:
    TcpRequest();
    TcpRequest(qint64 contentLength, const QDateTime &dateTime,
               const QHostAddress &hostAddress, quint64 port,
               const QString &authorizedToken, const QString &route,
               qint64 timeout, const QJsonObject &body);
    TcpRequest(const QJsonObject &jsonObj);
    ~TcpRequest() override;
    operator QJsonObject() const override;

private:
    QString m_authorizedToken;
    QString m_route;
    qint64 m_timeout = 0;
};

#endif // TCPREQUEST_H
