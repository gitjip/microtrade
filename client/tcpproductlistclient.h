#ifndef TCPPRODUCTLISTCLIENT_H
#define TCPPRODUCTLISTCLIENT_H

#include <tcpclient.h>

class TcpProductListClient : public TcpClient
{
    Q_OBJECT
public:
    explicit TcpProductListClient(QObject *parent = nullptr);
    void sendAsync(qint64 timeout);
};

#endif // TCPPRODUCTLISTCLIENT_H
