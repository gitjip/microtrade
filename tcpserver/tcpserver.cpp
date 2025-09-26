#include "tcpserver.h"
#include "tcprequest.h"
#include "tcpresponse.h"

TcpServer::TcpServer(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this))
{}

bool TcpServer::listen(const QHostAddress &hostAddress, qint64 port) {
    return m_server->listen(hostAddress, port);
}

void TcpServer::close() {
    m_server->close();
}

void TcpServer::onNewConnection() {
    qDebug() << "TcpServer::onNewConnection:";
    QTcpSocket *socket = m_server->nextPendingConnection();
    socketSet.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead() {
    qDebug() << "TcpServer::onReadyRead:";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
}

void TcpServer::onDisconnected() {
    qDebug() << "TcpServer::onDisconnected:";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    socketSet.remove(socket);
    socket->deleteLater();
}
