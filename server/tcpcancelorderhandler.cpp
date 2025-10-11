#include "tcpcancelorderhandler.h"
#include "authorization.h"
#include "tcplocalresponse.h"
#include "sqlauthenticator.h"
#include "sqlordermodifier.h"
#include "logmanager.h"

TcpCancelOrderHandler::TcpCancelOrderHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpCancelOrderHandler::handle(const TcpRequest &request) {
    QJsonObject body = request.body();
    if (!body.contains("authorization") || !body.contains("orderId")) {
        return TcpLocalResponse::make(false, TcpResponse::StatusType::InvalidRequest,
                                     "Missing required parameters");
    }

    Authorization auth = Authorization::fromJson(body["authorization"].toObject());
    qint64 orderId = body["orderId"].toDouble();

    // 验证用户权限
    SqlAuthenticator authenticator;
    User user = authenticator.exec(auth);
    if (user.isNull()) {
        // 记录未授权访问日志
        LogManager::getInstance()->warning("Unauthorized access attempt to cancel order");
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Unauthorized,
                                     "Unauthorized access");
    }

    // 尝试取消订单
    SqlOrderModifier orderModifier;
    bool success = orderModifier.cancelOrder(orderId, user.id());

    // 记录操作日志
    if (success) {
        LogManager::getInstance()->info(QString("Order cancelled successfully: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                     "Order cancelled successfully");
    } else {
        LogManager::getInstance()->warning(QString("Failed to cancel order: ID - %1 by user ID - %2").arg(orderId).arg(user.id()));
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                                     "Failed to cancel order");
    }
}