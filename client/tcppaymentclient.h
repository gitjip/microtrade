#ifndef TCPPAYMENTCLIENT_H
#define TCPPAYMENTCLIENT_H

#include "tcplocalclient.h"
#include "cart.h"

class TcpPaymentClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpPaymentClient(QObject *parent = nullptr);
    void sendAsync(const Cart &cart);
};

#endif // TCPPAYMENTCLIENT_H
