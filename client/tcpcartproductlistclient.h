#ifndef TCPCARTPRODUCTLISTCLIENT_H
#define TCPCARTPRODUCTLISTCLIENT_H

#include "tcplocalclient.h"

class TcpCartProductListClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpCartProductListClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPCARTPRODUCTLISTCLIENT_H
