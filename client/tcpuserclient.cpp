#include "tcpuserclient.h"
#include "authorization.h"
#include "authorizationmanager.h"

TcpUserClient::TcpUserClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpUserClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}
                                .toJson();
    TcpLocalClient::sendAsync("/user", body);
    qDebug() << Q_FUNC_INFO << body;
}
