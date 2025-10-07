#include "tcporderclient.h"
#include "authorization.h"
#include "commander.h"

TcpOrderClient::TcpOrderClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpOrderClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}.toJson();
    TcpLocalClient::sendAsync("/order", body);
}
