#include "tcpaddtocarthandler.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "tcplocalresponse.h"
#include "user.h"

TcpAddToCartHandler::TcpAddToCartHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpAddToCartHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate user
    SqlAuthenticator authenticator;
    User user = authenticator.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    // find cart by user id
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "cart not found");
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    // add connection between product and cart
    // unfinished ...
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully add to cart");
    qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
    return response;
}
