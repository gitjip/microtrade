#include "tcploginclient.h"
#include "authorizationmanager.h"
#include "config.h"
#include "user.h"

TcpLoginClient::TcpLoginClient(QObject *parent) : TcpClient{parent} {
    connectToHost(QHostAddress(Config::instance()->hostAddress()),
                  Config::instance()->port());
}

void TcpLoginClient::sendAsync(const QString &username, const QString &password,
                               qint64 timeout) {
    QJsonObject requestBody;
    requestBody[User::attributeToString(User::Attribute::Username)] = username;
    requestBody[User::attributeToString(User::Attribute::Password)] = password;
    TcpClient::sendAsync(
        TcpRequest(true, QDateTime::currentDateTime(),
                   QHostAddress(Config::instance()->hostAddress()),
                   Config::instance()->port(),
                   AuthorizationManager::instance()->m_token(), "/login",
                   timeout, requestBody),
        timeout);
    qDebug() << "TcpLoginClient::sendAsync:" << "username:" << username;
    qDebug() << "TcpLoginClient::sendAsync:" << "password:" << password;
}
