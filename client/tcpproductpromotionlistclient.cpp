#include "tcpproductpromotionlistclient.h"

TcpProductPromotionListClient::TcpProductPromotionListClient(QObject *parent)
    : TcpLocalClient{parent}
{}

void TcpProductPromotionListClient::sendAsync(qint64 productId){
    QJsonObject body;
    body["productId"] = productId;
    TcpLocalClient::sendAsync("/product-promotion-list", body);
}
