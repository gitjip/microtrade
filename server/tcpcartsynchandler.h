#ifndef TCPCARTSYNCHANDLER_H
#define TCPCARTSYNCHANDLER_H

#include <tcphandler.h>

class TcpCartSyncHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpCartSyncHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPCARTSYNCHANDLER_H
