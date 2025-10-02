#include "tcpproductlisthandler.h"
#include "config.h"
#include "sqlproductlistfinder.h"
#include <QJsonArray>

TcpProductListHandler::TcpProductListHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpProductListHandler::handle(const TcpRequest &tcpRequest) {
    Q_UNUSED(tcpRequest);
    SqlProductListFinder sqlProductListFinder;
    QList<Product> productList = sqlProductListFinder.exec();
    QJsonObject responseBody;
    QJsonArray responseBodyProductList;
    for (qsizetype i = 0; i < productList.count(); ++i) {
        responseBodyProductList.append(QJsonObject(productList[i]));
    }
    responseBody["product_list"] = responseBodyProductList;
    return TcpResponse(true, QDateTime::currentDateTime(),
                       QHostAddress(Config::instance()->hostAddress()),
                       Config::instance()->port(), true,
                       TcpResponse::StatusType::Success,
                       "successfully find product list", responseBody);
}
