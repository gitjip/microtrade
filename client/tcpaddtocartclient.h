#ifndef TCPADDTOCARTCLIENT_H
#define TCPADDTOCARTCLIENT_H

#include "tcplocalclient.h"

class TcpAddToCartClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpAddToCartClient(QObject *parent = nullptr);
    void sendAsync(qint64 productId);
};

#endif // TCPADDTOCARTCLIENT_H
