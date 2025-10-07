#include "tcploginhandler.h"
#include "authorization.h"
#include "sqlauthorizer.h"
#include "sqlloginchecker.h"
#include "tcplocalresponse.h"
#include "user.h"

TcpLoginHandler::TcpLoginHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpLoginHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlLoginChecker sqlUserIdFinder;
    User user =
        sqlUserIdFinder.exec(User::fromJson(requestBody["user"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "user not found");
        qDebug() << "TcpLoginHandler::handle" << response.toJson();
        return response;
    }
    SqlAuthorizer sqlAuthorizer;
    Authorization authorization = sqlAuthorizer.exec(user);
    if (authorization.isNull()) {
        TcpResponse response =
            TcpLocalResponse::make(false, TcpResponse::StatusType::Failed,
                "failed to create authorization");
        qDebug() << "TcpLoginHandler::handle" << response.toJson();
        return response;
    }
    QJsonObject responseBody;
    responseBody["authorization"] = authorization.toJson();
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
            "successfully create authorization", responseBody);
    // qDebug() << "TcpLoginHandler::handle" << response.toJson();
    return response;
}
