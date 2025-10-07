#ifndef TCPDISTRIBUTOR_H
#define TCPDISTRIBUTOR_H

#include "tcpserver_global.h"
#include "tcprequest.h"
#include "tcpresponse.h"
// #include "tcpserverthreadpool.h"
#include <QObject>

class TCPSERVER_EXPORT TcpDistributor : public QObject
{
    Q_OBJECT
public:
    explicit TcpDistributor(QObject *parent = nullptr);
    virtual TcpResponse distribute(const TcpRequest &tcpRequest) = 0;
    // void setMaxThreadCount(int maxThreadCount);

signals:

protected:
    // TcpServerThreadPool *m_threadPool;
};

#endif // TCPDISTRIBUTOR_H
