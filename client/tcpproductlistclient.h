#ifndef TCPPRODUCTLISTCLIENT_H
#define TCPPRODUCTLISTCLIENT_H

#include "tcplocalclient.h"

class TcpProductListClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpProductListClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPPRODUCTLISTCLIENT_H
