#include "tcploginclient.h"
#include "authorizationmanager.h"
#include "configure.h"
#include "user.h"

TcpLoginClient::TcpLoginClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Configure::instance()->hostAddress()),
                  Configure::instance()->port());
}

void TcpLoginClient::sendAsync(const QString &username, const QString &password,
                               qint64 timeout) {
    QJsonObject requestBody;
    requestBody[User::attributeToString(User::Attribute::Username)] = username;
    requestBody[User::attributeToString(User::Attribute::Password)] = password;
    TcpClient::sendAsync(
        TcpRequest(true, QDateTime::currentDateTime(),
                   QHostAddress(Configure::instance()->hostAddress()),
                   Configure::instance()->port(),
                   AuthorizationManager::instance()->authorizedToken(), "/login",
                   timeout, requestBody),
        timeout);
    qDebug() << "TcpLoginClient::sendAsync:" << "username:" << username;
    qDebug() << "TcpLoginClient::sendAsync:" << "password:" << password;
}
