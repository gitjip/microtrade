#ifndef TCPLOGINCLIENT_H
#define TCPLOGINCLIENT_H

#include "tcplocalclient.h"
#include "user.h"

class TcpLoginClient : public TcpLocalClient {
    Q_OBJECT
public:
    explicit TcpLoginClient(QObject *parent = nullptr);
    void sendAsync(const User &user);
};

#endif // TCPLOGINCLIENT_H
