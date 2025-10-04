#include "tcplocaldistributor.h"
#include "tcpaddtocarthandler.h"
#include "tcplocalresponse.h"
#include "tcploginhandler.h"
#include "tcplogouthandler.h"
#include "tcpproducthandler.h"
#include "tcpproductlisthandler.h"
#include "tcpregisterhandler.h"

TcpLocalDistributor::TcpLocalDistributor(QObject *parent)
    : TcpDistributor{parent} {}

TcpLocalDistributor *TcpLocalDistributor::instance() {
    static TcpLocalDistributor distributor;
    return &distributor;
}

TcpResponse TcpLocalDistributor::distribute(const TcpRequest &request) {
    TcpHandler *handler = nullptr;
    qDebug() << "TcpLocalDistributor::distribute:" << request.route();
    if (request.route() == "/login") {
        handler = new TcpLoginHandler(this);
    } else if (request.route() == "/product") {
        handler = new TcpProductHandler(this);
    } else if (request.route() == "/product-list") {
        handler = new TcpProductListHandler(this);
    } else if (request.route() == "/add-to-cart") {
        handler = new TcpAddToCartHandler(this);
    } else if (request.route() == "/register") {
        handler = new TcpRegisterHandler(this);
    } else if (request.route() == "/logout") {
        handler = new TcpLogoutHandler(this);
    }
    if (handler) {
        return handler->handle(request);
    } else {
        qDebug() << "TcpLocalDistributor::distribute:" << "handler is nullptr";
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::InvalidRequest,
            QString("route %1 not supported").arg(request.route()));
        return response;
    }
}
