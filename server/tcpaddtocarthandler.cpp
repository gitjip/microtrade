#include "tcpaddtocarthandler.h"
#include "sqluserfinder.h"
#include "user.h"
#include "tcplocalresponse.h"

TcpAddToCartHandler::TcpAddToCartHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpAddToCartHandler::handle(const TcpRequest &request) {
    SqlUserFinder userFinder;
    QJsonObject requestBody = request.body();
    User user = userFinder.exec(User::fromJson(requestBody["user"].toObject()));
    if (!user.isNull()) {
        TcpResponse response = TcpLocalResponse::make(false, TcpResponse::StatusType::Unauthorized, "not authorized");
        qDebug() << "TcpAddToCartHandler::handle:" << response.statusDetail();
        return response;
    }
    return {};
}
