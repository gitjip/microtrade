#ifndef TCPSERVERHANDLER_H
#define TCPSERVERHANDLER_H

#include "tcpserver_global.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include <QObject>
#include <QRunnable>

class TCPSERVER_EXPORT TcpServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerHandler(QObject *parent = nullptr);
    virtual TcpResponse handle(const TcpRequest &tcpRequest) = 0;

signals:
};

#endif // TCPSERVERHANDLER_H
