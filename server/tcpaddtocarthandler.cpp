#include "tcpaddtocarthandler.h"
#include "config.h"
#include "sqluserfinder.h"
#include "user.h"

TcpAddToCartHandler::TcpAddToCartHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpAddToCartHandler::handle(const TcpRequest &request) {
    SqlUserFinder userFinder;
    QJsonObject requestBody = request.body();
    User user = userFinder.exec(requestBody["user_id"].toString());
    if (!user.isValid()) {
        qDebug() << "TcpAddToCartHandler::handle:" << "unauthorized";
        return TcpResponse{true,
                           QDateTime::currentDateTime(),
                           QHostAddress(Config::instance()->hostAddress()),
                           Config::instance()->port(),
                           false,
                           TcpResponse::StatusType::Unauthorized,
                           "not authorized"};
    }

}
