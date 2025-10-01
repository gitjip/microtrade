#include "tcpserverproductlisthandler.h"
#include "configure.h"
#include "sqlproductlistfinder.h"
#include <QJsonArray>

TcpServerProductListHandler::TcpServerProductListHandler(QObject *parent)
    : TcpServerHandler{parent} {}

TcpResponse TcpServerProductListHandler::handle(const TcpRequest &tcpRequest) {
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
                       QHostAddress(Configure::instance()->hostAddress()),
                       Configure::instance()->port(), true,
                       TcpResponse::StatusType::Success,
                       "successfully find product list", responseBody);
}
