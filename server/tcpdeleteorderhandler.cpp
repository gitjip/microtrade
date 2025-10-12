#include "tcpdeleteorderhandler.h"
#include "authorization.h"
#include "tcplocalresponse.h"
#include "sqlauthenticator.h"
#include "sqlorderdeleter.h"
#include "logmanager.h"
#include "user.h"

TcpDeleteOrderHandler::TcpDeleteOrderHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpDeleteOrderHandler::handle(const TcpRequest &request) {
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
        LogManager::getInstance()->warning("Unauthorized access attempt to delete order");
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Unauthorized,
                                     "Unauthorized access");
    }
    
    // delete order
    SqlOrderDeleter orderDeleter;
    bool success = orderDeleter.exec(orderId, user.id());
    
    // success
    if (success) {
        LogManager::getInstance()->info(QString("Order deleted successfully: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                     "Order deleted successfully");
    } else {
        LogManager::getInstance()->warning(QString("Failed to delete order: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                                     "Failed to delete order");
    }
}