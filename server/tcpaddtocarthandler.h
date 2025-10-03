#ifndef TCPADDTOCARTHANDLER_H
#define TCPADDTOCARTHANDLER_H

#include <QObject>
#include <tcphandler.h>

class TcpAddToCartHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpAddToCartHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPADDTOCARTHANDLER_H
