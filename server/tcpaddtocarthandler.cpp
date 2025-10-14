#include "tcpaddtocarthandler.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "sqlcartitemcreator.h"
#include "tcplocalresponse.h"
#include "user.h"
#include "logmanager.h"

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
        LogManager::instance()->warning("Unauthorized access attempt to add to cart functionality");
        return response;
    }
    // find cart by user id
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "cart not found");
        LogManager::instance()->warning(QString("Cart not found for user ID: %1").arg(user.id()));
        return response;
    }
    qint64 productId = requestBody["product"].toObject()["id"].toDouble();
    
    // add cart item
    SqlCartItemCreator cartItemCreator;
    CartItem cartItem = cartItemCreator.exec(
        cart, Product::fromJson(requestBody["product"].toObject()));
    if (cartItem.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to create cart");
        LogManager::instance()->error(QString("Failed to add product ID: %1 to cart for user ID: %2").arg(productId).arg(user.id()));
        return response;
    }
    LogManager::instance()->info(QString("Product ID: %1 added to cart successfully for user ID: %2").arg(productId).arg(user.id()));
    
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully add to cart");
    return response;
}
