#ifndef TCPLOCALDISTRIBUTOR_H
#define TCPLOCALDISTRIBUTOR_H

#include <QObject>
#include "tcpdistributor.h"
#include "tcprequest.h"
#include "tcpresponse.h"

class TcpLocalDistributor : public TcpDistributor
{
    Q_OBJECT
public:
    static TcpLocalDistributor *instance();
    TcpResponse distribute(const TcpRequest &request) override;

private:
    explicit TcpLocalDistributor(QObject *parent = nullptr);
};

#endif // TCPLOCALDISTRIBUTOR_H
