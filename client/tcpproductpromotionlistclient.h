#ifndef TCPPRODUCTPROMOTIONLISTCLIENT_H
#define TCPPRODUCTPROMOTIONLISTCLIENT_H

#include "tcplocalclient.h"

class TcpProductPromotionListClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpProductPromotionListClient(QObject *parent = nullptr);
    void sendAsync(qint64 productId);
};

#endif // TCPPRODUCTPROMOTIONLISTCLIENT_H
