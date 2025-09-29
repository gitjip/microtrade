#include "tcpserver.h"
#include "tcprequest.h"
#include <QTimer>

TcpServer::TcpServer(TcpServerDistributor *distributor, QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this)),
    m_distributor(distributor) {
    connect(m_server, &QTcpServer::newConnection, this,
            &TcpServer::onNewConnection);
}

TcpServer *TcpServer::instance(TcpServerDistributor *distributor) {
    static TcpServer tcpServer(distributor);
    if (!tcpServer.m_distributor) {
        qDebug() << "TcpServer::instance:" << "distributor is null";
    }
    return &tcpServer;
}

bool TcpServer::listen(const QHostAddress &hostAddress, qint64 port) {
    qDebug() << "TcpServer::listen:" << hostAddress << port;
    return m_server->listen(hostAddress, port);
}

void TcpServer::close() { m_server->close(); }

void TcpServer::onNewConnection() {
    qDebug() << "TcpServer::onNewConnection:";
    QTcpSocket *socket = m_server->nextPendingConnection();
    m_socketSet.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead() {
    qDebug() << "TcpServer::onReadyRead:";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QTimer::singleShot(0, this, [this, socket]() {
        TcpResponse response =
            m_distributor->distribute(TcpRequest::fromSocket(socket));
        socket->write(response);
        qDebug() << "response sent:" << QJsonObject(response)
                 << "size:" << QByteArray(response).size();
    });
}

void TcpServer::onDisconnected() {
    qDebug() << "TcpServer::onDisconnected:";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    m_socketSet.remove(socket);
    socket->deleteLater();
}
