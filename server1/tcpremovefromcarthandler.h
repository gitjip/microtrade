#ifndef TCPREMOVEFROMCARTHANDLER_H
#define TCPREMOVEFROMCARTHANDLER_H

#include <tcphandler.h>

class TcpRemoveFromCartHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpRemoveFromCartHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPREMOVEFROMCARTHANDLER_H
