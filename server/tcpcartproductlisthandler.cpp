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
        qDebug() << Q_FUNC_INFO << response.statusDetail();
        return response;
    }
    // find cart by user id
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "not found cart");
        qDebug() << Q_FUNC_INFO << response.statusDetail();
        return response;
    }
    // find cart item list by cart id
    SqlCartItemListFinder cartItemListFinder;
    QList<CartItem> cartItemList = cartItemListFinder.exec(cart);
    // find product list by product id of carts
    SqlProductFinder productFinder;
    QJsonArray productJsonArray;
    for (qsizetype i = 0; i < cartItemList.count(); ++i) {
        Product product = productFinder.exec(Product{cartItemList[i].productId(),
                                                     {},
                                                     {},
                                                     "",
                                                     "",
                                                     -1,
                                                     -1,
                                                     Product::Category::Null});
        productJsonArray.append(product.toJson());
    }
    QJsonObject responseBody;
    responseBody["productList"] = productJsonArray;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find product list", responseBody);
    qDebug() << Q_FUNC_INFO << response.statusDetail();
    return response;
}
