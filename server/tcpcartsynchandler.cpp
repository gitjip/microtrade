#include "tcpcartsynchandler.h"
#include "cartitem.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "sqlcartsyncer.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpCartSyncHandler::TcpCartSyncHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpCartSyncHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator authenticator;
    User user = authenticator.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        return response;
    }
    // find cart
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "cart not found");
        return response;
    }
    // sync remote cart
    QJsonArray cartItemJsonArray = requestBody["cartItemList"].toArray();
    QList<CartItem> cartItemList;
    for (qsizetype i = 0; i < cartItemJsonArray.count(); ++i) {
        cartItemList.append(CartItem::fromJson(cartItemJsonArray[i].toObject()));
    }
    SqlCartSyncer cartSyncer;
    bool cartSyncSuccess = cartSyncer.exec(cart, cartItemList);
    if (!cartSyncSuccess) {
        TcpResponse response = TcpLocalResponse::make(false, TcpResponse::StatusType::Failed, "failed to sync all cart items");
        return response;
    }
    // success
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success, "success");
    return response;
}
