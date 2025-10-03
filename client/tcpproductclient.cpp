#include "tcpproductclient.h"
#include "authorizationmanager.h"
#include "config.h"
#include "product.h"

TcpProductClient::TcpProductClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Config::instance()->hostAddress()),
                  Config::instance()->port());
}

void TcpProductClient::sendAsync(const QString &productId, qint64 timeout) {
    QJsonObject requestBody;
    requestBody[Product::attributeToString(Product::Attribute::Id)] = productId;
    TcpClient::sendAsync(
        TcpRequest(true, QDateTime::currentDateTime(),
                   QHostAddress(Config::instance()->hostAddress()),
                   Config::instance()->port(),
                   AuthorizationManager::instance()->m_token(),
                   "/product", timeout, requestBody),
        timeout);
    qDebug() << "TcpProductClient::sendAsync:" << "productId:" << productId;
}
