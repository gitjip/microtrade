#ifndef TCPSERVERLOCALDISTRIBUTOR_H
#define TCPSERVERLOCALDISTRIBUTOR_H

#include <QObject>
#include "tcpserverdistributor.h"
#include "tcprequest.h"
#include "tcpresponse.h"

class TcpServerLocalDistributor : public TcpServerDistributor
{
    Q_OBJECT
public:
    explicit TcpServerLocalDistributor(QObject *parent = nullptr);
    TcpResponse distribute(const TcpRequest &tcpRequest) override;
};

#endif // TCPSERVERLOCALDISTRIBUTOR_H
