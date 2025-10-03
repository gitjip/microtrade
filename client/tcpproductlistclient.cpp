#include "tcpproductlistclient.h"

TcpProductListClient::TcpProductListClient(QObject *parent)
    : TcpLocalClient{parent} {}

void TcpProductListClient::sendAsync() {
    TcpLocalClient::sendAsync("/productList");
}
