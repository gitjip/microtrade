#ifndef TCPUSERCLIENT_H
#define TCPUSERCLIENT_H

#include "tcplocalclient.h"

class TcpUserClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpUserClient(QObject *parent = nullptr);
    void sendAsync();
};

#endif // TCPUSERCLIENT_H
