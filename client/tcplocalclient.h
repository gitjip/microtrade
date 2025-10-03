#ifndef TCPLOCALCLIENT_H
#define TCPLOCALCLIENT_H

#include "tcpclient.h"

class TcpLocalClient : public TcpClient
{
    Q_OBJECT
public:
    explicit TcpLocalClient(QObject *parent = nullptr);
    void sendAsync(const QString &route, const QJsonObject &body = {});
};

#endif // TCPLOCALCLIENT_H
