#include "tcplogouthandler.h"
#include "sqlunauthorizer.h"
#include "tcplocalresponse.h"

TcpLogoutHandler::TcpLogoutHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpLogoutHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlUnauthorizer unauthorizer;
    bool success = unauthorizer.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (!success) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to logout");
        qDebug() << "TcpLogoutHandler::handle:" << response.statusDetail();
        return response;
    }
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully logout");
    // qDebug() << "TcpLogoutHandler::handle:" << response.statusDetail();
    return response;
}
