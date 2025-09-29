#include "tcploginclient.h"
#include "authorizationmanager.h"
#include "configure.h"

TcpLoginClient::TcpLoginClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Configure::instance()->hostAddress()),
                  Configure::instance()->port());
}

void TcpLoginClient::sendAsync(const QString &username, const QString &password,
                               qint64 timeout) {
    TcpClient::sendAsync(
        TcpRequest(true, QDateTime::currentDateTime(),
                   QHostAddress(Configure::instance()->hostAddress()),
                   Configure::instance()->port(),
                   AuthorizationManager::instance()->authorizedToken(), "/login",
                   Configure::instance()->timeout(),
                   {{"username", username}, {"password", password}}),
        timeout);
    qDebug() << "TcpLoginClient::sendAsync:" << "username:" << username;
    qDebug() << "TcpLoginClient::sendAsync:" << "password:" << password;
}
