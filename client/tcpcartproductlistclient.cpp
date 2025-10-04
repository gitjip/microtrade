#include "tcpcartproductlistclient.h"
#include "authorization.h"
#include "authorizationmanager.h"

TcpCartProductListClient::TcpCartProductListClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpCartProductListClient::sendAsync() {
    QJsonObject requestBody;
    requestBody["authorization"] =
        Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}
                                       .toJson();
    TcpLocalClient::sendAsync("/cart-product-list", requestBody);
    qDebug() << "TcpCartProductListClient::sendAsync:"
             << requestBody;
}
