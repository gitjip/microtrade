#ifndef TCPPRODUCTHANDLER_H
#define TCPPRODUCTHANDLER_H

#include <QObject>
#include <tcphandler.h>

class TcpProductHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpProductHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPPRODUCTHANDLER_H
