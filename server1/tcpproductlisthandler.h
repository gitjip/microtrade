#ifndef TCPPRODUCTLISTHANDLER_H
#define TCPPRODUCTLISTHANDLER_H

#include <QObject>
#include <tcphandler.h>

class TcpProductListHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpProductListHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPPRODUCTLISTHANDLER_H
