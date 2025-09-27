#ifndef TCPSERVERTHREADPOOL_H
#define TCPSERVERTHREADPOOL_H

#include "tcpserverhandler.h"
#include <QObject>
#include <QThreadPool>

class TcpServerThreadPool : public QObject
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
