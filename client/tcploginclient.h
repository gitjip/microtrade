#ifndef TCPLOGINCLIENT_H
#define TCPLOGINCLIENT_H

#include "tcplocalclient.h"

class TcpLoginClient : public TcpLocalClient {
    Q_OBJECT
public:
    explicit TcpLoginClient(QObject *parent = nullptr);
    void sendAsync(const QString &username, const QString &passwordHash);
};

#endif // TCPLOGINCLIENT_H
