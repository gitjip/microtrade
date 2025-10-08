#include "tcpresetpasswordhandler.h"
#include "tcplocalresponse.h"
#include "sqlauthenticator.h"

TcpResetPasswordHandler::TcpResetPasswordHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpResetPasswordHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator authenticator;
    QString token=requestBody["authorizationToken"].toString();
    User user = authenticator.exec(Authorization{-1, {}, {}, -1, token});
    if(user.isNull()){
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // update password
    QString oldPasswordHash = requestBody["oldPasswordHash"].toString();
    QString newPasswordHash = requestBody["newPasswordHash"].toString();
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success, "success");
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
