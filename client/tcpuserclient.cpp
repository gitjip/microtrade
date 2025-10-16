#include "tcpuserclient.h"
#include "authorization.h"
#include "commander.h"

TcpUserClient::TcpUserClient(QObject *parent) : TcpLocalClient{parent} {}

void TcpUserClient::sendAsync() {
    QJsonObject body;
    body["authorization"] =
        Authorization{-1, {}, {}, -1, Commander::instance()->token()}
                                .toJson();
    TcpLocalClient::sendAsync("/user", body);
}
