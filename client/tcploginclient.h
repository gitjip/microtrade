#ifndef TCPLOGINCLIENT_H
#define TCPLOGINCLIENT_H

#include "tcpclient.h"
#include <QObject>

class TcpLoginClient : public TcpClient {
    Q_OBJECT
public:
    explicit TcpLoginClient(QObject *parent = nullptr);
    void sendAsync(const QString &username, const QString &password,
                   qint64 timeout = -1);
};

#endif // TCPLOGINCLIENT_H
