#include "tcporderhandler.h"
#include "sqlauthenticator.h"
#include "sqlorderitemlistfinder.h"
#include "sqlorderlistfinder.h"
#include "tcplocalresponse.h"
#include "logmanager.h"
#include <QJsonArray>

TcpOrderHandler::TcpOrderHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpOrderHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator authenticator;
    User user = authenticator.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        // 记录未授权访问日志
        LogManager::getInstance()->warning("Unauthorized access attempt to order information");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // find order tree
    SqlOrderListFinder orderListFinder;
    QList<Order> orderList = orderListFinder.exec(user.id());
    
    // 记录订单查询日志
    LogManager::getInstance()->info(QString("Order history query for user ID: %1, found %2 orders").arg(user.id()).arg(orderList.count()));
    
    QJsonArray orderTreeJsonArray;
    SqlOrderItemListFinder orderItemListFinder;
    for (qsizetype i = 0; i < orderList.count(); ++i) {
        QList<OrderItem> orderItemList = 
            orderItemListFinder.exec(orderList[i].id());
        QJsonArray orderItemJsonArray;
        for (qsizetype j = 0; j < orderItemList.count(); ++j) {
            orderItemJsonArray.append(orderItemList[j].toJson());
        }
        QJsonObject orderPair;
        orderPair["order"] = orderList[i].toJson();
        orderPair["orderItemList"] = orderItemJsonArray;
        orderTreeJsonArray.append(orderPair);
    }
    QJsonObject responseBody;
    responseBody["orderTree"] = orderTreeJsonArray;
    TcpResponse response = 
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find order tree", responseBody);
    // qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
