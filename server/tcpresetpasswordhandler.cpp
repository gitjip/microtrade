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
        // 记录未授权访问日志
        LogManager::getInstance()->warning("Unauthorized access attempt to password reset functionality");
        qDebug() << Q_FUNC_INFO << response.toJson();
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
        // 记录密码更新失败日志
        LogManager::getInstance()->error(QString("Password update failed for user ID: %1").arg(user.id()));
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // 记录密码更新成功日志
    LogManager::getInstance()->info(QString("Password updated successfully for user ID: %1").arg(user.id()));
    
    // success
    TcpResponse response = 
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success, "success");
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
