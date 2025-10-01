#include "tcpproductclient.h"
#include "authorizationmanager.h"
#include "configure.h"
#include "product.h"

TcpProductClient::TcpProductClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Configure::instance()->hostAddress()),
                  Configure::instance()->port());
}

void TcpProductClient::sendAsync(const QString &productId, qint64 timeout) {
    QJsonObject requestBody;
    requestBody[Product::attributeToString(Product::Attribute::Id)] = productId;
    TcpClient::sendAsync(
        TcpRequest(true, QDateTime::currentDateTime(),
                   QHostAddress(Configure::instance()->hostAddress()),
                   Configure::instance()->port(),
                   AuthorizationManager::instance()->authorizedToken(),
                   "/product", timeout, requestBody),
        timeout);
    qDebug() << "TcpProductClient::sendAsync:" << "productId:" << productId;
}
