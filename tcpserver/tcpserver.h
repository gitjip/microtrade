#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpserver_global.h"
#include "tcpserverdistributor.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPSERVER_EXPORT TcpServer : public QObject {
    Q_OBJECT
public:
    static TcpServer *instance(TcpServerDistributor *distributor = nullptr);   // single instance
    bool listen(const QHostAddress &hostAddress = QHostAddress::Any,
                qint64 port = 0);
    void close();

signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    explicit TcpServer(TcpServerDistributor *distributor, QObject *parent = nullptr);
    TcpServer(const TcpServer &tcpServer) = delete;
    TcpServer &operator=(const TcpServer &tcpServer) = delete;

private:
    QTcpServer *m_server;
    QSet<QTcpSocket *> m_socketSet;
    TcpServerDistributor *m_distributor;
};

#endif // TCPSERVER_H
