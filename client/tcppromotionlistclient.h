#ifndef TCPPROMOTIONLISTCLIENT_H
#define TCPPROMOTIONLISTCLIENT_H

#include "tcplocalclient.h"

class TcpPromotionListClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpPromotionListClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPPROMOTIONLISTCLIENT_H
