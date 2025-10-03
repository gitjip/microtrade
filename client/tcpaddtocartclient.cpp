#include "tcpaddtocartclient.h"
#include "authorizationmanager.h"
#include "product.h"

TcpAddToCartClient::TcpAddToCartClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpAddToCartClient::sendAsync(const Product &product) {
    QJsonObject body;
    body["product"] = product.toJson();
    body["authorization"] = AuthorizationManager::instance()->authorization().toJson();
    TcpLocalClient::sendAsync("addToCart", body);
}
