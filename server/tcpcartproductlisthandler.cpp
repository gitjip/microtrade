#include "tcpcartproductlisthandler.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "sqlcartitemlistfinder.h"
#include "sqlproductfinder.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpCartProductListHandler::TcpCartProductListHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpCartProductListHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate by token
    SqlAuthenticator authenticator;
    User user = authenticator.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        return response;
    }
    // find cart by user id
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "not found cart");
        return response;
    }
    // find cart item list by cart id
    SqlCartItemListFinder cartItemListFinder;
    QList<CartItem> cartItemList = cartItemListFinder.exec(cart);
    // find product list by product id of carts
    SqlProductFinder productFinder;
    QJsonArray productQuantityJsonArray;
    for (qsizetype i = 0; i < cartItemList.count(); ++i) {
        Product productId = {cartItemList[i].productId(), {}, {}, "", "", -1, -1,
                             Product::Category::Null};
        Product product = productFinder.exec(productId);
        QJsonObject productQuantityPair;
        productQuantityPair["product"] = product.toJson();
        productQuantityPair["quantity"] = cartItemList[i].quantity();
        productQuantityJsonArray.append(productQuantityPair);
    }
    QJsonObject responseBody;
    responseBody["productQuantityMap"] = productQuantityJsonArray;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find product list", responseBody);
    return response;
}
