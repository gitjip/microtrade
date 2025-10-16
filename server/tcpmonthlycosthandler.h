#ifndef TCPMONTHLYCOSTHANDLER_H
#define TCPMONTHLYCOSTHANDLER_H

#include <tcphandler.h>

class TcpMonthlyCostHandler : public TcpHandler
{
public:
    explicit TcpMonthlyCostHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPMONTHLYCOSTHANDLER_H
