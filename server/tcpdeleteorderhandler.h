#ifndef TCPDELETEORDERHANDLER_H
#define TCPDELETEORDERHANDLER_H

#include "tcphandler.h"
#include "tcprequest.h"
#include "tcpresponse.h"

class TcpDeleteOrderHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpDeleteOrderHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &request) override;
};

#endif // TCPDELETEORDERHANDLER_H