#include "tcpregisterhandler.h"
#include "sqlcartcreator.h"
#include "sqlusercreator.h"
#include "tcplocalresponse.h"

TcpRegisterHandler::TcpRegisterHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpRegisterHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    // create user
    SqlUserCreator userCreator;
    User user = userCreator.exec(User::fromJson(requestBody["user"].toObject()));
    if (user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to register");
        qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
        return response;
    }
    // create cart
    SqlCartCreator cartCreator;
    bool cartCreationSuccess = cartCreator.exec(user);
    if (!cartCreationSuccess) {
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::Failed, "failed to create cart");
        qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
        return response;
    }
    // success
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "successfully register");
    // qDebug() << "TcpRegisterHandler::handle:" << response.statusDetail();
    return response;
}
