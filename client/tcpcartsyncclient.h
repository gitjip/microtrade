#ifndef TCPCARTSYNCCLIENT_H
#define TCPCARTSYNCCLIENT_H

#include "tcplocalclient.h"
#include "cartitem.h"

class TcpCartSyncClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpCartSyncClient(QObject *parent = nullptr);
    void sendAsync(const QList<CartItem> &cartItem);
};

#endif // TCPCARTSYNCCLIENT_H
