#include "tcplocalserver.h"
#include "config.h"
#include "tcplocaldistributor.h"

TcpLocalServer::TcpLocalServer(QObject *parent) : TcpServer{parent} {
    m_server->listen(QHostAddress(Config::instance()->hostAddress()),
                     Config::instance()->port());
    qDebug() << Q_FUNC_INFO << Config::instance()->hostAddress()
             << Config::instance()->port();
}

TcpLocalServer *TcpLocalServer::instance() {
    static TcpLocalServer server;
    server.m_distributor = TcpLocalDistributor::instance();
    return &server;
}
