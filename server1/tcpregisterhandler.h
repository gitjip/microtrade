#ifndef TCPREGISTERHANDLER_H
#define TCPREGISTERHANDLER_H

#include <tcphandler.h>

class TcpRegisterHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpRegisterHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPREGISTERHANDLER_H
