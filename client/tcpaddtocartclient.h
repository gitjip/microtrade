#ifndef TCPADDTOCARTCLIENT_H
#define TCPADDTOCARTCLIENT_H

#include "tcplocalclient.h"
#include "product.h"

class TcpAddToCartClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpAddToCartClient(QObject *parent = nullptr);
    void sendAsync(const Product &product);
};

#endif // TCPADDTOCARTCLIENT_H
