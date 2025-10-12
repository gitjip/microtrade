#include "tcpcancelorderhandler.h"
#include "authorization.h"
#include "tcplocalresponse.h"
#include "sqlauthenticator.h"
#include "sqlordermodifier.h"
#include "logmanager.h"
#include "user.h"

TcpCancelOrderHandler::TcpCancelOrderHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpCancelOrderHandler::handle(const TcpRequest &request) {
    QJsonObject body = request.body();
    if (!body.contains("authorization") || !body.contains("orderId")) {
        return TcpLocalResponse::make(false, TcpResponse::StatusType::InvalidRequest,
                                     "Missing required parameters");
    }
    Authorization auth = Authorization::fromJson(body["authorization"].toObject());
    qint64 orderId = body["orderId"].toDouble();
    // authenticate
    SqlAuthenticator authenticator;
    User user = authenticator.exec(auth);
    if (user.isNull()) {
        LogManager::instance()->warning("Unauthorized access attempt to cancel order");
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Unauthorized,
                                     "Unauthorized access");
    }
    // cancel order
    SqlOrderModifier orderModifier;
    bool success = orderModifier.exec(orderId, user.id());
    // success
    if (success) {
        LogManager::instance()->info(QString("Order cancelled successfully: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                     "Order cancelled successfully");
    } else {
        LogManager::instance()->warning(QString("Failed to cancel order: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                                     "Failed to cancel order");
    }
}
