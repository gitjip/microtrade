#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpserver_global.h"
#include <QObject>

class TCPSERVER_EXPORT TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVER_H
