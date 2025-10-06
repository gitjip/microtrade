#ifndef TCPLOGOUTHANDLER_H
#define TCPLOGOUTHANDLER_H

#include <tcphandler.h>

class TcpLogoutHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpLogoutHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPLOGOUTHANDLER_H
