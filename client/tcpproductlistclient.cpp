#include "tcpproductlistclient.h"
#include "authorizationmanager.h"
#include "config.h"

TcpProductListClient::TcpProductListClient(QObject *parent)
    : TcpClient{parent} {
    connectToHost(QHostAddress(Config::instance()->hostAddress()),
                  Config::instance()->port());
}

void TcpProductListClient::sendAsync(qint64 timeout) {
    TcpRequest request(true, QDateTime::currentDateTime(),
                       QHostAddress(Config::instance()->hostAddress()),
                       Config::instance()->port(),
                       AuthorizationManager::instance()->m_token(),
                       "/product_list", timeout);
    TcpClient::sendAsync(request, timeout);
    qDebug() << "TcpProductListClient::sendAsync:" << QJsonObject(request);
}
