#ifndef TCPSERVERDISTRIBUTOR_H
#define TCPSERVERDISTRIBUTOR_H

#include <QObject>

class TcpHandlerFactory : public QObject
{
    Q_OBJECT
public:
    explicit TcpHandlerFactory(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERDISTRIBUTOR_H
