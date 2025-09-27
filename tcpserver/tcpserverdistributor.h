#ifndef TCPSERVERDISTRIBUTOR_H
#define TCPSERVERDISTRIBUTOR_H

#include "tcprequest.h"
#include "tcpresponse.h"
#include "tcpserverthreadpool.h"
#include <QObject>

class TcpServerDistributor : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerDistributor(QObject *parent = nullptr);
    TcpResponse distribute(const TcpRequest &tcpRequest);

signals:

private:
    TcpServerThreadPool *m_threadPool;
};

#endif // TCPSERVERDISTRIBUTOR_H
