#ifndef TCPPRODUCTCLIENT_H
#define TCPPRODUCTCLIENT_H

#include "product.h"
#include "tcplocalclient.h"

class TcpProductClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpProductClient(QObject *parent = nullptr);
    void sendAsync(const Product &product);
};

#endif // TCPPRODUCTCLIENT_H
