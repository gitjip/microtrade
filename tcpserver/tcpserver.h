#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpdistributor.h"
#include "tcpserver_global.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPSERVER_EXPORT TcpServer : public QObject {
    Q_OBJECT
public:
    // static TcpServer *instance(); // single instance
    bool listen(const QHostAddress &hostAddress, qint64 port);
    void close();

signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

protected:
    explicit TcpServer(QObject *parent = nullptr);
    TcpServer(const TcpServer &tcpServer) = delete;
    TcpServer &operator=(const TcpServer &tcpServer) = delete;

protected:
    QTcpServer *m_server;
    QSet<QTcpSocket *> m_socketSet;
    TcpDistributor *m_distributor = nullptr;
};

#endif // TCPSERVER_H
