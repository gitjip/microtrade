#include "tcplocaldistributor.h"
#include "tcpaddtocarthandler.h"
#include "tcpalterusernamehandler.h"
#include "tcpcancelorderhandler.h"
#include "tcpcartproductlisthandler.h"
#include "tcpcartsynchandler.h"
#include "tcplocalresponse.h"
#include "tcploginhandler.h"
#include "tcplogouthandler.h"
#include "tcporderhandler.h"
#include "tcppaymenthandler.h"
#include "tcpproducthandler.h"
#include "tcpproductlisthandler.h"
#include "tcpproductpromotionlisthandler.h"
#include "tcpproductsearchhandler.h"
#include "tcppromotionlisthandler.h"
#include "tcpregisterhandler.h"
#include "tcpremovefromcarthandler.h"
#include "tcpresetpasswordhandler.h"
#include "tcpuserhandler.h"
#include "tcpdeleteorderhandler.h"

TcpLocalDistributor::TcpLocalDistributor(QObject *parent)
    : TcpDistributor{parent} {}

TcpLocalDistributor *TcpLocalDistributor::instance() {
    static TcpLocalDistributor distributor;
    return &distributor;
}

TcpResponse TcpLocalDistributor::distribute(const TcpRequest &request) {
    TcpHandler *handler = nullptr;
    // qDebug() << "TcpLocalDistributor::distribute:" << request.route();
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
    } else if (request.route() == "/cart-product-list") {
        handler = new TcpCartProductListHandler(this);
    } else if (request.route() == "/user") {
        handler = new TcpUserHandler(this);
    } else if (request.route() == "/cart-sync") {
        handler = new TcpCartSyncHandler(this);
    } else if (request.route() == "/payment") {
        handler = new TcpPaymentHandler(this);
    } else if (request.route() == "/order") {
        handler = new TcpOrderHandler(this);
    } else if (request.route() == "/cancel-order") {
        handler = new TcpCancelOrderHandler(this);
    } else if (request.route() == "/delete-order") {
        handler = new TcpDeleteOrderHandler(this);
    } else if (request.route() == "/remove-from-cart") {
        handler = new TcpRemoveFromCartHandler(this);
    } else if (request.route() == "/promotion-list") {
        handler = new TcpPromotionListHandler(this);
    } else if (request.route() == "/product-promotion-list") {
        handler = new TcpProductPromotionListHandler(this);
    } else if (request.route() == "/alter-username") {
        handler = new TcpAlterUsernameHandler(this);
    } else if (request.route() == "/reset-password") {
        handler = new TcpResetPasswordHandler(this);
    } else if (request.route() == "/product-search") {
        handler = new TcpProductSearchHandler(this);
    }
    if (handler) {
        return handler->handle(request);
        handler->deleteLater();
    } else {
        qDebug() << "TcpLocalDistributor::distribute:" << "handler is nullptr";
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::InvalidRequest,
            QString("route %1 not supported").arg(request.route()));
        return response;
    }
}
