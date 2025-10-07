#include "tcpproductclient.h"
#include "product.h"

TcpProductClient::TcpProductClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpProductClient::sendAsync(qint64 productId) {
    QJsonObject body;
    body["product"] = Product(productId, {}, {}, "", "", -1, -1, Product::Category::Null).toJson();
    TcpLocalClient::sendAsync("/product", body);
}
