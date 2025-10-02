#ifndef TCPSERVERPAYMENTHANDLER_H
#define TCPSERVERPAYMENTHANDLER_H

#include <QObject>
#include <tcpserverhandler.h>

class TcpServerPaymentHandler : public TcpServerHandler
{
    Q_OBJECT
public:
    explicit TcpServerPaymentHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPSERVERPAYMENTHANDLER_H
