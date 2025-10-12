#include "tcpregisterhandler.h"
#include "sqlcartcreator.h"
#include "sqlusercreator.h"
#include "tcplocalresponse.h"
#include "logmanager.h"

TcpRegisterHandler::TcpRegisterHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpRegisterHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    
    // 获取用户名称用于日志
    QString username = requestBody["user"].toObject()["username"].toString();
    
    // create user
    SqlUserCreator userCreator;
    User user = userCreator.exec(User::fromJson(requestBody["user"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to register");
        // 记录用户注册失败日志
        LogManager::instance()->error(QString("User registration failed for username: %1").arg(username));
        qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
        return response;
    }
    // create cart
    SqlCartCreator cartCreator;
    bool cartCreationSuccess = cartCreator.exec(user);
    if (!cartCreationSuccess) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to create cart");
        // 记录购物车创建失败日志
        LogManager::instance()->error(QString("Cart creation failed for user ID: %1, username: %2").arg(user.id()).arg(username));
        qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
        return response;
    }
    // 记录注册成功日志
    LogManager::instance()->info(QString("User registered successfully: ID - %1, username - %2").arg(user.id()).arg(username));
    
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully register");
    // qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
    return response;
}
