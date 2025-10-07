#ifndef TCPSERVERTHREADPOOL_H
#define TCPSERVERTHREADPOOL_H

#include "tcpserver_global.h"
#include "tcpserverhandler.h"
#include <QObject>
#include <QThreadPool>

class TCPSERVER_EXPORT TcpServerThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerThreadPool(QObject *parent = nullptr);
    void setMaxThreadCount(int maxThreadCount);
    TcpResponse start(TcpServerHandler *handler, const TcpRequest &tcpRequest);

signals:

private:
    QThreadPool *m_threadPool;
};

#endif // TCPSERVERTHREADPOOL_H
