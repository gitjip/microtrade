#include "tcplocaldistributor.h"
#include "config.h"
#include "tcploginhandler.h"
#include "tcppaymenthandler.h"
#include "tcpproducthandler.h"
#include "tcpproductlisthandler.h"

TcpLocalDistributor::TcpLocalDistributor(QObject *parent)
    : TcpDistributor{parent} {}

TcpLocalDistributor *TcpLocalDistributor::instance(){
    static TcpLocalDistributor distributor;
    return &distributor;
}

TcpResponse
TcpLocalDistributor::distribute(const TcpRequest &tcpRequest) {
    TcpHandler *tcpServerHandler = nullptr;
    qDebug() << "TcpServerLocalDistributor::distribute:" << tcpRequest.route();
    if (tcpRequest.route() == "/login") {
        tcpServerHandler = new TcpLoginHandler(this);
    } else if (tcpRequest.route() == "/product") {
        tcpServerHandler = new TcpProductHandler(this);
    } else if (tcpRequest.route() == "/product_list") {
        tcpServerHandler = new TcpProductListHandler(this);
    } else if (tcpRequest.route() == "/pay") {
        tcpServerHandler = new TcpPaymentHandler(this);
    } else {
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Config::instance()->hostAddress()),
                           Config::instance()->port(), false,
                           TcpResponse::StatusType::InvalidRequest,
                           QString("request of route \"%1\" not supported")
                               .arg(tcpRequest.route()));
    }
    return tcpServerHandler->handle(tcpRequest);
}
