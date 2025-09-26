#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpserver_global.h"
#include "tcpserverdistributor.h"
#include "tcpserverparser.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPSERVER_EXPORT TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    bool listen(const QHostAddress &hostAddress = QHostAddress::Any, qint64 port = 0);
    void close();

signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpServer *m_server;
    QSet<QTcpSocket *> m_socketSet;
    TcpServerParser *m_parser;
    TcpServerDistributor *m_distributor;
};

#endif // TCPSERVER_H
