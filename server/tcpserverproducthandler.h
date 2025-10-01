#ifndef TCPSERVERPRODUCTHANDLER_H
#define TCPSERVERPRODUCTHANDLER_H

#include <QObject>
#include <tcpserverhandler.h>

class TcpServerProductHandler : public TcpServerHandler
{
    Q_OBJECT
public:
    explicit TcpServerProductHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPSERVERPRODUCTHANDLER_H
