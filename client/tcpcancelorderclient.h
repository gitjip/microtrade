#ifndef TCPCANCELORDERCLIENT_H
#define TCPCANCELORDERCLIENT_H

#include "tcplocalclient.h"

class TcpCancelOrderClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpCancelOrderClient(QObject *parent = nullptr);
    void sendAsync(qint64 orderId);
};

#endif // TCPCANCELORDERCLIENT_H