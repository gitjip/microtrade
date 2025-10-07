#ifndef TCPCLIENTSENDER_H
#define TCPCLIENTSENDER_H

#include <QObject>

class TcpClientSender : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientSender(QObject *parent = nullptr);

signals:
};

#endif // TCPCLIENTSENDER_H
