#include "tcpproductsearchhandler.h"
#include "sqlproductsearcher.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpProductSearchHandler::TcpProductSearchHandler(QObject *parent)
    : TcpHandler(parent) {}

TcpResponse TcpProductSearchHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    QString keyword = requestBody["keyword"].toString().trimmed();
    SqlProductSearcher searcher;
    QList<Product> products = searcher.exec(keyword);
    QJsonObject responseBody;
    QJsonArray productArray;
    for (const auto &product : std::as_const(products)) {
        productArray.append(product.toJson());
    }
    responseBody["searchResult"] = productArray;
    TcpResponse response = TcpLocalResponse::make(
        true, TcpResponse::StatusType::Success, "success", responseBody);
    qDebug() << Q_FUNC_INFO << response.toJson();
    return response;
}
