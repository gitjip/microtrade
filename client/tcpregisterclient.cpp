#include "tcpregisterclient.h"
#include "user.h"

TcpRegisterClient::TcpRegisterClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpRegisterClient::sendAsync(const QString &username,
                                  const QString &passwordHash,
                                  const QUrl &imageUrl) {
    QJsonObject body;
    body["user"] = User(-1, {}, {}, username, passwordHash, imageUrl).toJson();
    TcpRequest request;
    TcpLocalClient::sendAsync("/register", body);
}
