#include "tcpproductsearchclient.h"

TcpProductSearchClient::TcpProductSearchClient(QObject *parent)
    : TcpLocalClient{parent}
{}

void TcpProductSearchClient::sendAsync(const QString& keyword) {
    QJsonObject body;
    body["keyword"] = keyword;
    TcpLocalClient::sendAsync("/product-search", body);
}
