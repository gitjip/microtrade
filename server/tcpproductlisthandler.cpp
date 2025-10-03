#include "tcpproductlisthandler.h"
#include "sqlproductlistfinder.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpProductListHandler::TcpProductListHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpProductListHandler::handle(const TcpRequest &request) {
    Q_UNUSED(request);
    SqlProductListFinder sqlProductListFinder;
    QList<Product> productList = sqlProductListFinder.exec();
    QJsonObject responseBody;
    QJsonArray responseBodyProductList;
    for (qsizetype i = 0; i < productList.count(); ++i) {
        responseBodyProductList.append(productList[i].toJson());
    }
    responseBody["productList"] = responseBodyProductList;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
            "successfully find product list", responseBody);
    qDebug() << "TcpProductListHandler::handle" << response.toJson();
    return response;
}
