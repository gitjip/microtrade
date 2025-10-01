#include "tcpserverloginhandler.h"
#include "configure.h"
#include "sqltokengenerator.h"
#include "sqluseridfinder.h"
#include "user.h"

TcpServerLoginHandler::TcpServerLoginHandler(QObject *parent)
    : TcpServerHandler{parent} {}

TcpResponse TcpServerLoginHandler::handle(const TcpRequest &tcpRequest) {
    SqlUserIdFinder sqlUserIdFinder;
    QJsonObject requestBody = tcpRequest.body();
    QString userId = sqlUserIdFinder.exec(requestBody[User::attributeToString(User::Attribute::Username)].toString(),
                                          requestBody[User::attributeToString(User::Attribute::Password)].toString());
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:" << "user not found";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false, TcpResponse::StatusType::NotFound,
                           "user not found");
    }
    SqlTokenGenerator sqlTokenGenerator;
    QString token = sqlTokenGenerator.exec(userId);
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:"
                 << "failed to generate authorized_token";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false, TcpResponse::StatusType::Failed,
                           "failed to generate authorized_token");
    }
    qDebug() << "TcpServerLoginHandler::handle:"
             << "successfully generate token:" << token;
    return TcpResponse(true, QDateTime::currentDateTime(),
                       QHostAddress(Configure::instance()->hostAddress()),
                       Configure::instance()->port(), true, TcpResponse::StatusType::Success,
                       "successfully generate token",
                       {{TcpResponse::attributeToString(TcpResponse::Attribute::AuthorizedToken), token}});
}
