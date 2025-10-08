#ifndef TCPPRODUCTSEARCHCLIENT_H
#define TCPPRODUCTSEARCHCLIENT_H

#include "tcplocalclient.h"

class TcpProductSearchClient : public TcpLocalClient
{
    Q_OBJECT
public:
    explicit TcpProductSearchClient(QObject *parent = nullptr);
    void sendAsync(const QString& keyword);
};

#endif // TCPPRODUCTSEARCHCLIENT_H
