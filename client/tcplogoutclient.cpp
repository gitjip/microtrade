#include "tcplogoutclient.h"
#include "authorization.h"
#include "authorizationmanager.h"

TcpLogoutClient::TcpLogoutClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpLogoutClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}.toJson();
    TcpLocalClient::sendAsync("/logout", body);
}
