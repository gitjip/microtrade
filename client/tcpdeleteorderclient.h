#ifndef TCPDELETEORDERCLIENT_H
#define TCPDELETEORDERCLIENT_H

#include "tcplocalclient.h"

class TcpDeleteOrderClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpDeleteOrderClient(QObject *parent = nullptr);
    void sendAsync(qint64 orderId);
};

#endif // TCPDELETEORDERCLIENT_H