#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpclient_global.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include <QObject>
#include <QTcpSocket>

class TCPCLIENT_EXPORT TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToHost(const QHostAddress &hostAddress, qint64 port);
    void sendAsync(const TcpRequest &tcpRequest, qint64 timeout = -1);

signals:
    void readyRead(const TcpResponse &tcpResponse);
    void timedOut();
    void errorOccurred();

private:
    bool send(const TcpRequest &tcpRequest);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
