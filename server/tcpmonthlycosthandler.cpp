#include "tcpmonthlycosthandler.h"
#include "authorization.h"
#include "sqlauthenticator.h"
#include "sqlmonthlycostserver.h"
#include "tcplocalresponse.h"

TcpMonthlyCostHandler::TcpMonthlyCostHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpMonthlyCostHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator sqlAuthenticator;
    QString token = requestBody["authorizationToken"].toString();
    Authorization authorization{-1, {}, {}, -1, token};
    User user = sqlAuthenticator.exec(authorization);
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        return response;
    }
    // monthly cost
    SqlMonthlyCostServer monthlyCostServer;
    int year = requestBody["year"].toInt();
    int month = requestBody["month"].toInt();
    double cost = monthlyCostServer.exec(user.id(), year, month);
    if (cost == -1) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to get monthly cost");
        return response;
    }
    // success
    QJsonObject responseBody;
    responseBody["cost"] = cost;
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "success", responseBody);
    return response;
}
