#include "tcpaddtocartclient.h"
#include "authorization.h"
#include "commander.h"
#include "product.h"

TcpAddToCartClient::TcpAddToCartClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpAddToCartClient::sendAsync(qint64 productId) {
    QJsonObject body;
    body["product"] =
        Product(productId, {}, {}, "", "", -1, -1, Product::Category::Null).toJson();
    body["authorization"] =
        Authorization(-1, {}, {}, -1, Commander::instance()->token()).toJson();
    TcpLocalClient::sendAsync("/add-to-cart", body);
}
