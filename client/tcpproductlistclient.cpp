#include "tcpproductlistclient.h"
#include "authorizationmanager.h"
#include "configure.h"

TcpProductListClient::TcpProductListClient(QObject *parent)
    : TcpClient{parent} {
    connectToHost(QHostAddress(Configure::instance()->hostAddress()),
                  Configure::instance()->port());
}

void TcpProductListClient::sendAsync(qint64 timeout) {
    TcpRequest request(true, QDateTime::currentDateTime(),
                       QHostAddress(Configure::instance()->hostAddress()),
                       Configure::instance()->port(),
                       AuthorizationManager::instance()->authorizedToken(),
                       "/product_list", timeout);
    TcpClient::sendAsync(request, timeout);
    qDebug() << "TcpProductListClient::sendAsync:" << QJsonObject(request);
}
