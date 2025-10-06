#ifndef TCPREMOVEFROMCARTCLIENT_H
#define TCPREMOVEFROMCARTCLIENT_H

#include "tcplocalclient.h"

class TcpRemoveFromCartClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpRemoveFromCartClient(QObject *parent = nullptr);
    void sendAsync(qint64 productId);
};

#endif // TCPREMOVEFROMCARTCLIENT_H
