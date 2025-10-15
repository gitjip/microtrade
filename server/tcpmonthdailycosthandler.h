#ifndef TCPMONTHDAILYCOSTHANDLER_H
#define TCPMONTHDAILYCOSTHANDLER_H

#include <tcphandler.h>

class TcpMonthDailyCostHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpMonthDailyCostHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPMONTHDAILYCOSTHANDLER_H
