#ifndef TCPPAYMENTHANDLER_H
#define TCPPAYMENTHANDLER_H

#include <tcphandler.h>

class TcpPaymentHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpPaymentHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPPAYMENTHANDLER_H
