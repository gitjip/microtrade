#ifndef TCPLOGOUTCLIENT_H
#define TCPLOGOUTCLIENT_H

#include "tcplocalclient.h"

class TcpLogoutClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpLogoutClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPLOGOUTCLIENT_H
