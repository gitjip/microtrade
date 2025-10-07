#include "tcppaymentclient.h"
#include "authorization.h"
#include "commander.h"

TcpPaymentClient::TcpPaymentClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpPaymentClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}.toJson();
    TcpLocalClient::sendAsync("/payment", body);
}
