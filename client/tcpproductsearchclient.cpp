#include "tcpproductsearchclient.h"
#include <QJsonArray>

TcpProductSearchClient::TcpProductSearchClient(QObject *parent)
    : TcpLocalClient{parent}
{}

void TcpProductSearchClient::sendAsync(const QStringList& tokens) {
    QJsonObject body;
    body["tokens"] = QJsonArray::fromStringList(tokens);
    TcpLocalClient::sendAsync("/product-search", body);
}
