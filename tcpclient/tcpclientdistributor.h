#ifndef TCPCLIENTDISTRIBUTOR_H
#define TCPCLIENTDISTRIBUTOR_H

#include <QObject>

class TcpClientDistributor : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientDistributor(QObject *parent = nullptr);

signals:
};

#endif // TCPCLIENTDISTRIBUTOR_H
