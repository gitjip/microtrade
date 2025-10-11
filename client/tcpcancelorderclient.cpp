#include "authorization.h"
#include "commander.h"

TcpCancelOrderClient::TcpCancelOrderClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpCancelOrderClient::sendAsync(qint64 orderId) {
    QJsonObject body;
    body["authorization"] = 
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}.toJson();
    body["orderId"] = orderId;
    TcpLocalClient::sendAsync("/order/cancel", body);
}