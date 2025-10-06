#include "tcpcartproductlistclient.h"
#include "authorization.h"
#include "commander.h"

TcpCartProductListClient::TcpCartProductListClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpCartProductListClient::sendAsync() {
    QJsonObject requestBody;
    requestBody["authorization"] =
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}
                                       .toJson();
    TcpLocalClient::sendAsync("/cart-product-list", requestBody);
    qDebug() << "TcpCartProductListClient::sendAsync:"
             << requestBody;
}
