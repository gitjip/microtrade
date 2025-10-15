#include "tcpresetpasswordhandler.h"
#include "sqlauthenticator.h"
#include "sqlpasswordupdater.h"
#include "tcplocalresponse.h"
#include "logmanager.h"

TcpResetPasswordHandler::TcpResetPasswordHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpResetPasswordHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator authenticator;
    QString token = requestBody["authorizationToken"].toString();
    User user = authenticator.exec(Authorization{-1, {}, {}, -1, token});
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        LogManager::instance()->warning("Unauthorized access attempt to password reset functionality");
        return response;
    }
    // update password
    SqlPasswordUpdater passwordUpdater;
    QString oldPasswordHash = requestBody["oldPasswordHash"].toString();
    QString newPasswordHash = requestBody["newPasswordHash"].toString();
    bool isPasswordUpdated = 
        passwordUpdater.exec(user.id(), oldPasswordHash, newPasswordHash);
    if (!isPasswordUpdated) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to update password");
        LogManager::instance()->error(QString("Password update failed for user ID: %1").arg(user.id()));
        return response;
    }
    LogManager::instance()->info(QString("Password updated successfully for user ID: %1").arg(user.id()));
    
    // success
    TcpResponse response = 
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success, "success");
    return response;
}
