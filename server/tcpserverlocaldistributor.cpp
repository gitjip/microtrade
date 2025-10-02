#include "tcpserverlocaldistributor.h"
#include "configure.h"
#include "tcpserverloginhandler.h"
#include "tcpserverpaymenthandler.h"
#include "tcpserverproducthandler.h"
#include "tcpserverproductlisthandler.h"

TcpServerLocalDistributor::TcpServerLocalDistributor(QObject *parent)
    : TcpServerDistributor{parent} {}

TcpResponse
TcpServerLocalDistributor::distribute(const TcpRequest &tcpRequest) {
    TcpServerHandler *tcpServerHandler = nullptr;
    qDebug() << "TcpServerLocalDistributor::distribute:" << tcpRequest.route();
    if (tcpRequest.route() == "/login") {
        tcpServerHandler = new TcpServerLoginHandler(this);
    } else if (tcpRequest.route() == "/product") {
        tcpServerHandler = new TcpServerProductHandler(this);
    } else if (tcpRequest.route() == "/product_list") {
        tcpServerHandler = new TcpServerProductListHandler(this);
    } else if (tcpRequest.route() == "/pay") {
        tcpServerHandler = new TcpServerPaymentHandler(this);
    } else {
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false,
                           TcpResponse::StatusType::InvalidRequest,
                           QString("request of route \"%1\" not supported")
                               .arg(tcpRequest.route()));
    }
    return tcpServerHandler->handle(tcpRequest);
}
