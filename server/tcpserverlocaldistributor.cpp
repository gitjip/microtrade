#include "tcpserverlocaldistributor.h"
#include "configure.h"
#include "tcpserverloginhandler.h"

TcpServerLocalDistributor::TcpServerLocalDistributor(QObject *parent)
    : TcpServerDistributor{parent} {}

TcpResponse
TcpServerLocalDistributor::distribute(const TcpRequest &tcpRequest) {
    TcpServerHandler *tcpServerHandler = nullptr;
    if (tcpRequest.route() == "/login") {
        qDebug() << "TcpServerLocalDistributor::distribute" << "/login";
        tcpServerHandler = new TcpServerLoginHandler(this);
    } else {
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false, "unknown_request",
                           "");
    }
    return tcpServerHandler->handle(tcpRequest);
}
