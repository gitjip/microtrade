#include "tcpdeleteorderclient.h"
#include "authorization.h"
#include "commander.h"

TcpDeleteOrderClient::TcpDeleteOrderClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpDeleteOrderClient::sendAsync(qint64 orderId) {
    QJsonObject body;
    body["authorization"] = 
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}.toJson();
    body["orderId"] = orderId;
    TcpLocalClient::sendAsync("/delete-order", body);
}