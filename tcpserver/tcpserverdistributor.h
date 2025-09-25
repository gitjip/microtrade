#ifndef TCPSERVERDISTRIBUTOR_H
#define TCPSERVERDISTRIBUTOR_H

#include <QObject>

class TcpServerDistributor : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerDistributor(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERDISTRIBUTOR_H
