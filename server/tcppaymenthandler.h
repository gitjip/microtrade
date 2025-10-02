#ifndef TCPPAYMENTHANDLER_H
#define TCPPAYMENTHANDLER_H

#include <QObject>
#include <tcphandler.h>

class TcpPaymentHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpPaymentHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPPAYMENTHANDLER_H
