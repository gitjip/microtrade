#ifndef TCPSERVERLOGINHANDLER_H
#define TCPSERVERLOGINHANDLER_H

#include <QObject>
#include "tcpserverhandler.h"

class TcpServerLoginHandler : public TcpServerHandler
{
    Q_OBJECT
public:
    explicit TcpServerLoginHandler(QObject *parent = nullptr);
    TcpResponse handle(const TcpRequest &tcpRequest) override;
};

#endif // TCPSERVERLOGINHANDLER_H
