#ifndef TCPREGISTERCLIENT_H
#define TCPREGISTERCLIENT_H

#include "tcplocalclient.h"

class TcpRegisterClient : public TcpLocalClient {
    Q_OBJECT
public:
    explicit TcpRegisterClient(QObject *parent = nullptr);
    void sendAsync(const QString &username, const QString &passwordHash,
                   const QUrl &imageUrl = {});
};

#endif // TCPREGISTERCLIENT_H
