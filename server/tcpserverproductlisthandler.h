#ifndef TCPSERVERPRODUCTLISTHANDLER_H
#define TCPSERVERPRODUCTLISTHANDLER_H

#include <QObject>
#include <tcpserverhandler.h>

class TcpServerProductListHandler : public TcpServerHandler
{
    Q_OBJECT
public:
    explicit TcpServerProductListHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPSERVERPRODUCTLISTHANDLER_H
