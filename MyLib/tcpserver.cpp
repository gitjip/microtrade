#include "tcpserver.h"

namespace My {
TcpServer::TcpServer(QObject *parent) : QTcpServer{parent} {}

void TcpServer::onNewConnection() {
    QTcpSocket *socket = nextPendingConnection();
    socketList.append(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    Request req = QJsonDocument::fromJson(socket->readAll()).object();
    emit readyWrite(socket, req);
}

void TcpServer::onDisconnected() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    socketList.removeOne(socket);
    socket->deleteLater();
}
} // namespace My
