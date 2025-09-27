#include "tcpserver.h"
#include "tcprequest.h"

TcpServer::TcpServer(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this)),
    m_distributor(new TcpServerDistributor(this)) {}

bool TcpServer::listen(const QHostAddress &hostAddress, qint64 port) {
    return m_server->listen(hostAddress, port);
}

void TcpServer::close() {
    m_server->close();
}

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
    socket->write(m_distributor->distribute(TcpRequest::fromSocket(socket)));
}

void TcpServer::onDisconnected() {
    qDebug() << "TcpServer::onDisconnected:";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    m_socketSet.remove(socket);
    socket->deleteLater();
}
