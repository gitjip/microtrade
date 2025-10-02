#include "tcpproducthandler.h"
#include "config.h"
#include "sqlproductfinder.h"

TcpProductHandler::TcpProductHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpProductHandler::handle(const TcpRequest &tcpRequest) {
    SqlProductFinder sqlProductFinder;
    QJsonObject requestBody = tcpRequest.body();
    Product product = sqlProductFinder.exec(
        requestBody[Product::attributeToString(Product::Attribute::Id)]
            .toString());
    if (!product.isValid()) {
        qDebug() << "TcpServerProductHandler::handle:" << "product not found";
        return TcpResponse(true, QDateTime::currentDateTime(),
                           QHostAddress(Config::instance()->hostAddress()),
                           Config::instance()->port(), false,
                           TcpResponse::StatusType::NotFound, "product not found");
    }
    qDebug() << "TcpServerProductHandler::handle:"
             << "successfully find product";
    QJsonObject responseBody;
    responseBody["product"] = QJsonObject(product);
    return TcpResponse(true, QDateTime::currentDateTime(),
                       QHostAddress(Config::instance()->hostAddress()),
                       Config::instance()->port(), true,
                       TcpResponse::StatusType::Success,
                       "successfully find product", responseBody);
}
