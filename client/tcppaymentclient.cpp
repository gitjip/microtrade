#include "tcppaymentclient.h"
#include "authorizationmanager.h"
#include "configure.h"
#include "product.h"

TcpPaymentClient::TcpPaymentClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Configure::instance()->hostAddress()),
                  Configure::instance()->port());
}

void TcpPaymentClient::sendAsync(const QString &productId, qint64 timeout) {
    QJsonObject requestBody;
    requestBody[Product::attributeToString(Product::Attribute::Id)] = productId;
    TcpRequest request(true, QDateTime::currentDateTime(),
                       QHostAddress(Configure::instance()->hostAddress()),
                       Configure::instance()->port(),
                       AuthorizationManager::instance()->authorizedToken(),
                       "/pay", timeout, requestBody);
    TcpClient::sendAsync(request, timeout);
    qDebug() << "TcpPaymentClient::sendAsync:" << "productId:" << productId;
}
