#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpclient_global.h"
#include <QObject>

class TCPCLIENT_EXPORT TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

signals:
};

#endif // TCPCLIENT_H
