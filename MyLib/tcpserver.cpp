#include "tcpserver.h"

namespace My {
TcpServer::TcpServer(QObject *parent) : QTcpServer{parent} {
    connect(this, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

void TcpServer::onNewConnection() {
    qDebug() << "服务器有新连接";
    QTcpSocket *socket = nextPendingConnection();
    socketList.append(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead() {
    qDebug() << "服务器接收信息";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    Request req = QJsonDocument::fromJson(socket->readAll()).object();
    qDebug() << req.method << req.route
             << QJsonDocument(req.headers).toJson(QJsonDocument::Compact)
             << QJsonDocument(req.body.toObject()).toJson(QJsonDocument::Compact);
    emit readyWrite(socket, req);
}

void TcpServer::onDisconnected() {
    qDebug() << "服务器断开一个连接";
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    socketList.removeOne(socket);
    socket->deleteLater();
}
} // namespace My
