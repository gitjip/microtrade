#ifndef TCPLOCALSERVER_H
#define TCPLOCALSERVER_H

#include <tcpserver.h>

class TcpLocalServer : public TcpServer
{
    Q_OBJECT
public:
    static TcpLocalServer *instance();

private:
    explicit TcpLocalServer(QObject *parent = nullptr);
};

#endif // TCPLOCALSERVER_H
