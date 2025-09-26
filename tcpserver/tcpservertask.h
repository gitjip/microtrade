#ifndef TCPSERVERTASK_H
#define TCPSERVERTASK_H

#include <QObject>

class TcpServerTask : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerTask(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERTASK_H
