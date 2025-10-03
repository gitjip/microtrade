#ifndef TCPLOGINHANDLER_H
#define TCPLOGINHANDLER_H

#include "tcphandler.h"

class TcpLoginHandler : public TcpHandler
{
    Q_OBJECT
public:
    explicit TcpLoginHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPLOGINHANDLER_H
