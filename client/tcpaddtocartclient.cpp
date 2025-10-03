#include "tcpaddtocartclient.h"
#include "authorizationmanager.h"
#include "product.h"

TcpAddToCartClient::TcpAddToCartClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpAddToCartClient::sendAsync(qint64 productId) {
    QJsonObject body;
    body["product"] = Product(productId, {}, {}, "", "", -1, -1, Product::Category::Null).toJson();
    body["authorization"] = AuthorizationManager::instance()->authorization().toJson();
    TcpLocalClient::sendAsync("/add-to-cart", body);
}
