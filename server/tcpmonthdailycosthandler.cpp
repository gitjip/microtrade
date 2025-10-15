#include "tcpmonthdailycosthandler.h"
#include "sqlauthenticator.h"
#include "tcplocalresponse.h"
#include "sqlmonthdailycostserver.h"

TcpMonthDailyCostHandler::TcpMonthDailyCostHandler(QObject *parent)
    : TcpHandler{parent}
{}

TcpResponse TcpMonthDailyCostHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // authenticate
    SqlAuthenticator sqlAuthenticator;
    QString token = requestBody["authorizationToken"].toString();
    Authorization authorization{-1, {}, {}, -1, token};
    User user = sqlAuthenticator.exec(authorization);
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // month daily cost
    SqlMonthDailyCostServer monthDailyCostServer;
    int year = requestBody["year"].toInt();
    int month = requestBody["month"].toInt();
    QJsonArray costArray = monthDailyCostServer.exec(user.id(), year, month);
    if (costArray.isEmpty()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "cost array is empty");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // success
    QJsonObject responseBody;
    responseBody["costArray"] = costArray;
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "success", responseBody);
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
