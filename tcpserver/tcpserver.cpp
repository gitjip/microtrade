#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this))
{}

bool TcpServer::listen(const QHostAddress &hostAddress, qint64 port) {
    return m_server->listen(hostAddress, port);
}

void TcpServer::close() {
    m_server->close();
}
