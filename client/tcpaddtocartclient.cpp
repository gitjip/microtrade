#include "tcpaddtocartclient.h"
#include "authorizationmanager.h"
#include "config.h"
#include "product.h"

TcpAddToCartClient::TcpAddToCartClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Config::instance()->hostAddress()),
                  Config::instance()->port());
}

void TcpAddToCartClient::sendAsync(const QString &productId, qint64 timeout) {
    QJsonObject requestBody;
    requestBody[Product::attributeToString(Product::Attribute::Id)] = productId;
    TcpRequest request(true, QDateTime::currentDateTime(),
                       QHostAddress(Config::instance()->hostAddress()),
                       Config::instance()->port(),
                       AuthorizationManager::instance()->m_token(),
                       "/add_to_cart", timeout, requestBody);
    TcpClient::sendAsync(request, timeout);
    qDebug() << "TcpPaymentClient::sendAsync:" << "productId:" << productId;
}
