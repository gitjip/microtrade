#ifndef TCPCARTPRODUCTLISTHANDLER_H
#define TCPCARTPRODUCTLISTHANDLER_H

#include <tcphandler.h>

class TcpCartProductListHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpCartProductListHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPCARTPRODUCTLISTHANDLER_H
