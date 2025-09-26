#ifndef TCPSERVERTHREADPOOL_H
#define TCPSERVERTHREADPOOL_H

#include <QObject>
#include <QThreadPool>

class TcpServerThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerThreadPool(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERTHREADPOOL_H
