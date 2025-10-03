#include "tcpproductclient.h"

TcpProductClient::TcpProductClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpProductClient::sendAsync(const Product &product) {
    QJsonObject body;
    body["product"] = product.toJson();
    TcpLocalClient::sendAsync("/product", body);
}
