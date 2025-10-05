#include "tcporderclient.h"
#include "authorization.h"
#include "authorizationmanager.h"

TcpOrderClient::TcpOrderClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpOrderClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}
                                .toJson();
    TcpLocalClient::sendAsync("/order", body);
}
