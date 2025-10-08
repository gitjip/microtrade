#include "tcpresetpasswordclient.h"
#include "commander.h"

TcpResetPasswordClient::TcpResetPasswordClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpResetPasswordClient::sendAsync(const QString &oldPasswordHash,
                                       const QString &newPasswordHash) {
    QJsonObject body;
    body["authorizationToken"] = Commander::instance()->token();
    body["oldPasswordHash"] = oldPasswordHash;
    body["newPasswordHash"] = newPasswordHash;
    TcpLocalClient::sendAsync("/reset-password", body);
}
