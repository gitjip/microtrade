#ifndef TCPHANDLERFACTORY_H
#define TCPHANDLERFACTORY_H

#include <QObject>

class TcpHandlerFactory : public QObject
{
    Q_OBJECT
public:
    explicit TcpHandlerFactory(QObject *parent = nullptr);

signals:
};

#endif // TCPHANDLERFACTORY_H
