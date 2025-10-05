#ifndef TCPORDERCLIENT_H
#define TCPORDERCLIENT_H

#include "tcplocalclient.h"

class TcpOrderClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpOrderClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPORDERCLIENT_H
