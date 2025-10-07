#include "tcploginclient.h"
#include "user.h"

TcpLoginClient::TcpLoginClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpLoginClient::sendAsync(const QString &username, const QString &passwordHash) {
    QJsonObject body;
    body["user"] = User(-1, {}, {}, username, passwordHash).toJson();
    TcpLocalClient::sendAsync("/login", body);
}
