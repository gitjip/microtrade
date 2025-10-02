#include "tcploginhandler.h"
#include "config.h"
#include "sqlauthorizer.h"
#include "sqlauthenticator.h"
#include "user.h"

TcpLoginHandler::TcpLoginHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpLoginHandler::handle(const TcpRequest &tcpRequest) {
    SqlAuthenticator sqlUserIdFinder;
    QJsonObject requestBody = tcpRequest.body();
    QString userId = sqlUserIdFinder.exec(
        requestBody[User::attributeToString(User::Attribute::Username)]
            .toString(),
        requestBody[User::attributeToString(User::Attribute::Password)]
            .toString());
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:" << "user not found";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Config::instance()->hostAddress()),
                           Config::instance()->port(), false,
                           TcpResponse::StatusType::NotFound, "user not found");
    }
    SqlAuthorizer sqlTokenGenerator;
    QString token = sqlTokenGenerator.exec(userId);
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:"
                 << "failed to generate authorized_token";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Config::instance()->hostAddress()),
                           Config::instance()->port(), false,
                           TcpResponse::StatusType::Failed,
                           "failed to generate authorized_token");
    }
    qDebug() << "TcpServerLoginHandler::handle:"
             << "successfully generate token:" << token;
    return TcpResponse(
        true, QDateTime::currentDateTime(),
        QHostAddress(Config::instance()->hostAddress()),
        Config::instance()->port(), true, TcpResponse::StatusType::Success,
        "successfully generate token",
        {{TcpResponse::attributeToString(TcpResponse::Attribute::Authorization),
          token}});
}
