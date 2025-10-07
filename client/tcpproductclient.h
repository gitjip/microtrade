#ifndef TCPPRODUCTCLIENT_H
#define TCPPRODUCTCLIENT_H

#include "tcplocalclient.h"

class TcpProductClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpProductClient(QObject *parent = nullptr);
    void sendAsync(qint64 productId);
};

#endif // TCPPRODUCTCLIENT_H
