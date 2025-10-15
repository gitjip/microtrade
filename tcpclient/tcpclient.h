#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpclient_global.h"
#include "tcprequest.h"
#include "tcpresponse.h"
#include <QTcpSocket>

class TCPCLIENT_EXPORT TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToHost(const QHostAddress &hostAddress, qint64 port);
    void sendAsync(const TcpRequest &request, qint64 maxTime = -1);

signals:
    void readyRead(const TcpResponse &tcpResponse);
    void timeout();
    void notOpened();
    void writtingErrorOccurred();

private:
    bool send(const TcpRequest &tcpRequest);

private:
    QTcpSocket *m_socket;
};

#endif // TCPCLIENT_H
