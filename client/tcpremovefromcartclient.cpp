#include "tcpremovefromcartclient.h"
#include "authorization.h"
#include "commander.h"

TcpRemoveFromCartClient::TcpRemoveFromCartClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpRemoveFromCartClient::sendAsync(qint64 productId) {
    QJsonObject body;
    body["productId"] = productId;
    body["authorization"] =
        Authorization(-1, {}, {}, -1, Commander::instance()->token()).toJson();
    TcpLocalClient::sendAsync("/remove-from-cart", body);
}
