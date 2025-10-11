#include "tcpcancelorderhandler.h"
#include "authorization.h"
#include "order.h"
#include "sqllogwriter.h"
#include "sqlauthorizer.h"
#include "tcplocalresponse.h"
#include "sqlordermodifier.h"

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
    SqlAuthorizer authorizer;
    if (!authorizer.authorize(auth)) {
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Unauthorized,
                                     "Unauthorized access");
    }

    // 尝试取消订单
    SqlOrderModifier orderModifier;
    bool success = orderModifier.cancelOrder(orderId, auth.userId());

    // 记录操作日志
    SqlLogWriter::instance()->addLog(auth.userId(), 
                                    success ? "Cancel order succeeded" : "Cancel order failed", 
                                    request.route(), body);

    if (success) {
        return TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                     "Order cancelled successfully");
    } else {
        return TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                                     "Failed to cancel order");
    }
}