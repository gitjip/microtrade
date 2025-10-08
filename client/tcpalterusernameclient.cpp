#include "tcpalterusernameclient.h"
#include "commander.h"

TcpAlterUsernameClient::TcpAlterUsernameClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpAlterUsernameClient::sendAsync(const QString &username) {
    QJsonObject body;
    body["username"] = username;
    body["authorizationToken"] = Commander::instance()->token();
    TcpLocalClient::sendAsync("/alter-username", body);
}
