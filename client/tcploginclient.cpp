#include "tcploginclient.h"

TcpLoginClient::TcpLoginClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpLoginClient::sendAsync(const User &user) {
    QJsonObject body;
    body["user"] = user.toJson();
    TcpLocalClient::sendAsync("/login", body);
}
