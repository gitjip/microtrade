#include "tcplogouthandler.h"
#include "sqlunauthorizer.h"
#include "tcplocalresponse.h"
#include "logmanager.h"

TcpLogoutHandler::TcpLogoutHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpLogoutHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlUnauthorizer unauthorizer;
    bool success = unauthorizer.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (!success) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to logout");
        // 记录登出失败日志
        LogManager::getInstance()->warning("Logout failed");
        qDebug() << "TcpLogoutHandler::handle:" << response.statusDetail();
        return response;
    }
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully logout");
    // 记录登出成功日志
    LogManager::getInstance()->info("User logout successful");
    // qDebug() << "TcpLogoutHandler::handle:" << response.statusDetail();
    return response;
}
