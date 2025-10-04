#include "tcpcartproductlisthandler.h"

TcpCartProductListHandler::TcpCartProductListHandler(QObject *parent)
    : TcpHandler{parent}
{}

TcpResponse TcpCartProductListHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    return {};
}
