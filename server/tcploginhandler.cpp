#include "tcploginhandler.h"
#include "authorization.h"
#include "sqlauthorizer.h"
#include "sqlloginchecker.h"
#include "tcplocalresponse.h"
#include "user.h"
#include "logmanager.h"

TcpLoginHandler::TcpLoginHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpLoginHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlLoginChecker sqlUserIdFinder;
    User user = 
        sqlUserIdFinder.exec(User::fromJson(requestBody["user"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "user not found");
        // 记录登录失败日志
        LogManager::instance()->warning(QString("Login failed: User not found - username: %1").arg(
            requestBody["user"].toObject()["username"].toString()));
        qDebug() << "TcpLoginHandler::handle" << response.toJson();
        return response;
    }
    SqlAuthorizer sqlAuthorizer;
    Authorization authorization = sqlAuthorizer.exec(user);
    if (authorization.isNull()) {
        TcpResponse response = 
            TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                "failed to create authorization");
        LogManager::instance()->error(QString("Failed to create authorization for user ID: %1").arg(user.id()));
        qDebug() << "TcpLoginHandler::handle" << response.toJson();
        return response;
    }
    QJsonObject responseBody;
    responseBody["authorization"] = authorization.toJson();
    TcpResponse response = 
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
            "successfully create authorization", responseBody);
    LogManager::instance()->info(QString("User login successful: ID - %1").arg(user.id()));
    // qDebug() << "TcpLoginHandler::handle" << response.toJson();
    return response;
}
