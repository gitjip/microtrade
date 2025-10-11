#ifndef TCPCANCELORDERHANDLER_H
#define TCPCANCELORDERHANDLER_H

#include "tcphandler.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include "sqlordermodifier.h"

class TcpCancelOrderHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpCancelOrderHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
}; 

#endif // TCPCANCELORDERHANDLER_H