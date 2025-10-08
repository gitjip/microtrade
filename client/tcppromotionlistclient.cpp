#include "tcppromotionlistclient.h"

TcpPromotionListClient::TcpPromotionListClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpPromotionListClient::sendAsync() {
    TcpLocalClient::sendAsync("/promotion-list");
}
