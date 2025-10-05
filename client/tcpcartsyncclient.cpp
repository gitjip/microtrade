#include "tcpcartsyncclient.h"
#include "authorization.h"
#include "authorizationmanager.h"
#include <QJsonArray>

TcpCartSyncClient::TcpCartSyncClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpCartSyncClient::sendAsync(const QList<CartItem> &cartItemList) {
    QJsonObject body;
    body["authorization"] =
            Authorization{-1, {}, {}, -1, AuthorizationManager::instance()->token()}
            .toJson();
    QJsonArray cartItemJsonArray;
    for (qsizetype i = 0; i < cartItemList.count(); ++i) {
        cartItemJsonArray.append(cartItemList[i].toJson());
    }
    body["cartItemList"] = cartItemJsonArray;
    TcpLocalClient::sendAsync("/cart-sync", body);
}
