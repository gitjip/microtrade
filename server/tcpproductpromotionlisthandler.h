#ifndef TCPPRODUCTPROMOTIONLISTHANDLER_H
#define TCPPRODUCTPROMOTIONLISTHANDLER_H

#include <tcphandler.h>

class TcpProductPromotionListHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpProductPromotionListHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request);
};

#endif // TCPPRODUCTPROMOTIONLISTHANDLER_H
