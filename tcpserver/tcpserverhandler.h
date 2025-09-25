#ifndef TCPSERVERHANDLER_H
#define TCPSERVERHANDLER_H

#include <QObject>

class TcpHandler : public QObject
{
    Q_OBJECT
public:
    explicit TcpHandler(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERHANDLER_H
