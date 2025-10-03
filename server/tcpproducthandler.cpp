#include "tcpproducthandler.h"
#include "sqlproductfinder.h"
#include "tcplocalresponse.h"

TcpProductHandler::TcpProductHandler(QObject *parent) : TcpHandler{parent} {}

TcpResponse TcpProductHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    SqlProductFinder sqlProductFinder;
    Product product = sqlProductFinder.exec(
        Product::fromJson(requestBody["product"].toObject()));
    if (product.isNull()) {
        qDebug() << "TcpServerProductHandler::handle:" << "product not found";
        TcpResponse response = TcpLocalResponse::make(
            false, TcpResponse::StatusType::NotFound, "product not found");
        qDebug() << "TcpProductHandler::handle" << response.toJson();
        return response;
    }
    QJsonObject responseBody;
    responseBody["product"] = product.toJson();
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
            "successfully find product", responseBody);
    qDebug() << "TcpProductHandler::handle:" << response.toJson();
    return response;
}
