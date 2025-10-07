#ifndef TCPORDERHANDLER_H
#define TCPORDERHANDLER_H

#include <tcphandler.h>

class TcpOrderHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpOrderHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPORDERHANDLER_H
