#include "tcpalterusernamehandler.h"
#include "authorization.h"
#include "sqlauthenticator.h"
#include "sqlusernameupdater.h"
#include "tcplocalresponse.h"

TcpAlterUsernameHandler::TcpAlterUsernameHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpAlterUsernameHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    QString token = requestBody["authorizationToken"].toString();
    SqlAuthenticator authenticator;
    User user = authenticator.exec(Authorization{-1, {}, {}, -1, token});
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // update username
    SqlUsernameUpdater usernameUpdater;
    QString username = requestBody["username"].toString();
    bool isUsernameUpdated = usernameUpdater.exec(user.id(), username);
    if (!isUsernameUpdated) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to update username");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "success");
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
