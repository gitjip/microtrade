#ifndef TCPPROMOTIONLISTHANDLER_H
#define TCPPROMOTIONLISTHANDLER_H

#include <tcphandler.h>

class TcpPromotionListHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpPromotionListHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPPROMOTIONLISTHANDLER_H
