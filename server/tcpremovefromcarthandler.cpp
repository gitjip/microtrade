#include "tcpremovefromcarthandler.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "sqlcartitemremover.h"
#include "tcplocalresponse.h"
#include "user.h"

TcpRemoveFromCartHandler::TcpRemoveFromCartHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpRemoveFromCartHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate user
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
            false, TcpResponse::StatusType::NotFound, "cart not found");
        qDebug() << Q_FUNC_INFO << response.statusDetail();
        return response;
    }
    // remove cart item
    SqlCartItemRemover cartItemRemover;
    qint64 productId = requestBody["productId"].toInteger();
    bool isCartItemRemoved = cartItemRemover.exec(cart.id(), productId);
    if (!isCartItemRemoved) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to remove from cart");
        qDebug() << Q_FUNC_INFO << response.statusDetail();
        return response;
    }
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully add to cart");
    qDebug() << Q_FUNC_INFO << response.statusDetail();
    return response;
}
