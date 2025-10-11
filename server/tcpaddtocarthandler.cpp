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
        // 记录未授权访问日志
        LogManager::getInstance()->warning("Unauthorized access attempt to add to cart functionality");
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    // find cart by user id
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "cart not found");
        // 记录购物车未找到日志
        LogManager::getInstance()->warning(QString("Cart not found for user ID: %1").arg(user.id()));
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    // 获取商品ID用于日志
    qint64 productId = requestBody["product"].toObject()["id"].toDouble();
    
    // add cart item
    SqlCartItemCreator cartItemCreator;
    CartItem cartItem = cartItemCreator.exec(
        cart, Product::fromJson(requestBody["product"].toObject()));
    if (cartItem.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to create cart");
        // 记录添加失败日志
        LogManager::getInstance()->error(QString("Failed to add product ID: %1 to cart for user ID: %2").arg(productId).arg(user.id()));
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    // 记录添加成功日志
    LogManager::getInstance()->info(QString("Product ID: %1 added to cart successfully for user ID: %2").arg(productId).arg(user.id()));
    
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully add to cart");
    // qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
    return response;
}
