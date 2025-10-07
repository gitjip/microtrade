#include "tcpuserhandler.h"
#include "sqlauthenticator.h"
#include "sqluserfinder.h"
#include "tcplocalresponse.h"

TcpUserHandler::TcpUserHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpUserHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlAuthenticator authenticator;
    // authorize
    User user = authenticator.exec(
        Authorization::fromJson(requestBody["authorization"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // find user by its id
    SqlUserFinder userFinder;
    User returned = userFinder.exec(user);
    if (returned.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "not found user");
        qDebug() << Q_FUNC_INFO << response.toJson();
        return response;
    }
    // success
    QJsonObject responseBody;
    responseBody["user"] = returned.toJson();
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find user", responseBody);
    // qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
