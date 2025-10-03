#ifndef TCPADDTOCARTCLIENT_H
#define TCPADDTOCARTCLIENT_H

#include <QObject>
#include <tcpclient.h>

class TcpAddToCartClient : public TcpClient
{
    Q_OBJECT
public:
    explicit TcpAddToCartClient(QObject *parent = nullptr);
    void sendAsync(const QString &productId, qint64 timeout);
};

#endif // TCPADDTOCARTCLIENT_H
