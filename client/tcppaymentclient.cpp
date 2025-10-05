#include "tcppaymentclient.h"
#include "authorization.h"
#include "authorizationmanager.h"

TcpPaymentClient::TcpPaymentClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpPaymentClient::sendAsync(const Cart &cart) {
    QJsonObject body;
    body["cart"] = cart.toJson();
    body["authorization"] =
            Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}
            .toJson();
    TcpLocalClient::sendAsync("/payment", body);
}
