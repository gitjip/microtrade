#include "tcpserverloginhandler.h"
#include "configure.h"
#include "sqltokengenerator.h"
#include "sqluseridfinder.h"

TcpServerLoginHandler::TcpServerLoginHandler(QObject *parent)
    : TcpServerHandler{parent} {}

TcpResponse TcpServerLoginHandler::handle(const TcpRequest &tcpRequest) {
    SqlUserIdFinder sqlUserIdFinder;
    QJsonObject requestBody = tcpRequest.body();
    QString userId = sqlUserIdFinder.exec(requestBody["username"].toString(),
                                          requestBody["password"].toString());
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:" << "user not found";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false, "not_found",
                           "user not found");
    }
    SqlTokenGenerator sqlTokenGenerator;
    QString token = sqlTokenGenerator.exec(userId);
    if (userId.isEmpty()) {
        qDebug() << "TcpServerLoginHandler::handle:"
                 << "failed to generate authorized_token";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Configure::instance()->hostAddress()),
                           Configure::instance()->port(), false, "runtime_error",
                           "failed to generate authorized_token");
    }
    qDebug() << "TcpServerLoginHandler::handle:"
             << "successfully generate token" + token;
    return TcpResponse(true, QDateTime::currentDateTime(),
                       QHostAddress(Configure::instance()->hostAddress()),
                       Configure::instance()->port(), true, "success",
                       "successfully generate token",
                       {{"authorized_token", token}});
}
