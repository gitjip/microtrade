#ifndef TCPPAYMENTCLIENT_H
#define TCPPAYMENTCLIENT_H

#include <QObject>
#include <tcpclient.h>

class TcpPaymentClient : public TcpClient
{
    Q_OBJECT
public:
    explicit TcpPaymentClient(QObject *parent = nullptr);
    void sendAsync(const QString &productId, qint64 timeout);
};

#endif // TCPPAYMENTCLIENT_H
