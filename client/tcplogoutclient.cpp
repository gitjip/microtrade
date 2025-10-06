#include "tcplogoutclient.h"
#include "authorization.h"
#include "commander.h"

TcpLogoutClient::TcpLogoutClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpLogoutClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}.toJson();
    TcpLocalClient::sendAsync("/logout", body);
}
