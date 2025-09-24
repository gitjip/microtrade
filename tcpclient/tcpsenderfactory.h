#ifndef TCPSENDERFACTORY_H
#define TCPSENDERFACTORY_H

#include <QObject>

class TcpSenderFactory : public QObject
{
    Q_OBJECT
public:
    explicit TcpSenderFactory(QObject *parent = nullptr);

signals:
};

#endif // TCPSENDERFACTORY_H
