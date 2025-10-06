#ifndef TCPUSERHANDLER_H
#define TCPUSERHANDLER_H

#include <tcphandler.h>

class TcpUserHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpUserHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPUSERHANDLER_H
