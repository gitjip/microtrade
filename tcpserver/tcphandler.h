#ifndef TCPHANDLER_H
#define TCPHANDLER_H

#include "tcpserver_global.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include <QObject>

class TCPSERVER_EXPORT TcpHandler : public QObject
{
    Q_OBJECT
public:
    explicit TcpHandler(QObject *parent = nullptr);
    virtual TcpResponse handle(const TcpRequest &tcpRequest) = 0;

signals:
};

#endif // TCPHANDLER_H
