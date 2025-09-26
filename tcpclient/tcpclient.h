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
    void sendAsync(const TcpRequest &tcpRequest);
    void sendAsync(const TcpRequest &tcpRequest, qint64 timeout);

signals:
    void readyRead(const TcpResponse &tcpResponse);

private:
    // return false if an error occurred
    bool parseSend(const TcpRequest &tcpRequest);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
