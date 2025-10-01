#ifndef TCPPRODUCTCLIENT_H
#define TCPPRODUCTCLIENT_H

#include <QObject>
#include <tcpclient.h>

class TcpProductClient : public TcpClient
{
    Q_OBJECT
public:
    explicit TcpProductClient(QObject *parent = nullptr);
    void sendAsync(const QString &productId, qint64 timeout);
};

#endif // TCPPRODUCTCLIENT_H
