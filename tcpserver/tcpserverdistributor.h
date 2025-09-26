#ifndef TCPSERVERDISTRIBUTOR_H
#define TCPSERVERDISTRIBUTOR_H

#include "tcprequest.h"
#include "tcpresponse.h"
#include <QObject>

class TcpServerDistributor : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerDistributor(QObject *parent = nullptr);
    TcpResponse distribute(const TcpRequest &tcpRequest);

signals:
};

#endif // TCPSERVERDISTRIBUTOR_H
