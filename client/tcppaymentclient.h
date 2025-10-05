#ifndef TCPPAYMENTCLIENT_H
#define TCPPAYMENTCLIENT_H

#include "tcplocalclient.h"

class TcpPaymentClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpPaymentClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPPAYMENTCLIENT_H
