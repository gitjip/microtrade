#include "tcporderhandler.h"
#include "sqlauthenticator.h"
#include "sqlorderitemlistfinder.h"
#include "sqlorderlistfinder.h"
#include "tcplocalresponse.h"
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
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // find order tree
    SqlOrderListFinder orderListFinder;
    QList<Order> orderList = orderListFinder.exec(user.id());
    // SqlOrderTreeFinder orderTreeFinder;
    // QMap<Order, QList<OrderItem>> orderTree = orderTreeFinder.exec(user.id());
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
    // QMapIterator it(orderTree);
    // while (it.hasNext()) {
    //     it.next();
    //     QJsonObject orderPair;
    //     orderPair["order"] = it.key().toJson();
    //     QJsonArray orderItemJsonArray;
    //     for (qsizetype i = 0; i < it.value().count(); ++i) {
    //         orderItemJsonArray.append(it.value()[i].toJson());
    //     }
    //     orderPair["orderItemList"] = orderItemJsonArray;
    //     orderTreeJsonArray.append(orderPair);
    // }
    QJsonObject responseBody;
    responseBody["orderTree"] = orderTreeJsonArray;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find order tree", responseBody);
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
