#include "tcppaymenthandler.h"
#include "costcalculatorwithpromotion.h"
#include "sqlauthenticator.h"
#include "sqlcartfinder.h"
#include "sqlcartitemlistfinder.h"
#include "sqlordercreator.h"
#include "sqlorderitemcreator.h"
#include "sqlproductfinder.h"
#include "sqlproductreducer.h"
#include "sqlpromotionfinder.h"
#include "sqlpromotionidlistfinder.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpPaymentHandler::TcpPaymentHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpPaymentHandler::handle(const TcpRequest &request) {
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
    // find cart
    SqlCartFinder cartFinder;
    Cart cart = cartFinder.exec(user);
    if (cart.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "cart not found");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // find cart item list
    SqlCartItemListFinder cartItemListFinder;
    QList<CartItem> cartItemList = cartItemListFinder.exec(cart);
    // find product list
    SqlProductFinder productFinder;
    QMap<Product, qint64> quantityMap;
    for (qsizetype i = 0; i < cartItemList.count(); ++i) {
        Product product = productFinder.exec(Product{cartItemList[i].productId(),
                                                     {},
                                                     {},
                                                     "",
                                                     "",
                                                     -1,
                                                     -1,
                                                     Product::Category::Null});
        quantityMap.insert(product, cartItemList[i].quantity());
    }
    // reduce the stock
    SqlProductReducer productReducer;
    quantityMap = productReducer.exec(quantityMap);
    if (quantityMap.isEmpty()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "order is empty");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // find promotion list
    SqlPromotionIdListFinder promotionIdListFinder;
    SqlPromotionFinder promotionFinder;
    // calculate cost list and total cost
    QMap<Product, double> costMap;
    double totalCost = 0;
    QMapIterator quantityIt(quantityMap);
    while (quantityIt.hasNext()) {
        quantityIt.next();
        QList<qint64> promotionIdList =
            promotionIdListFinder.exec(quantityIt.key().id());
        QList<Promotion> promotionList;
        for (qsizetype i = 0; i < promotionIdList.count(); ++i) {
            Promotion promotion = promotionFinder.exec(promotionIdList[i]);
            promotionList.append(promotion);
        }
        costMap[quantityIt.key()] = CostCalculatorWithPromotion::calculate(
            quantityIt.key().price(), quantityIt.value(), promotionList);
        totalCost += costMap[quantityIt.key()];
    }
    // create order
    SqlOrderCreator orderCreator;
    qint64 orderId = orderCreator.exec(user, totalCost);
    if (orderId == -1) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to create order");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // create order item list
    SqlOrderItemCreator orderItemCreator;
    bool isOrderItemListCreated = true;
    QMapIterator costIt(costMap);
    quantityIt.toFront();
    while (quantityIt.hasNext() && costIt.hasNext()) {
        quantityIt.next();
        costIt.next();
        qint64 orderItemId = orderItemCreator.exec(
            orderId, quantityIt.key().id(), quantityIt.value(), costIt.value());
        if (orderItemId == -1) {
            isOrderItemListCreated = false;
        }
    }
    if (!isOrderItemListCreated) {
        TcpResponse response =
            TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                                                      "failed to create all order items");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // success
    QJsonObject responseBody;
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully pay", responseBody);
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
