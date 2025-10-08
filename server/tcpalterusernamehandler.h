#ifndef TCPALTERUSERNAMEHANDLER_H
#define TCPALTERUSERNAMEHANDLER_H

#include <tcphandler.h>

class TcpAlterUsernameHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpAlterUsernameHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPALTERUSERNAMEHANDLER_H
