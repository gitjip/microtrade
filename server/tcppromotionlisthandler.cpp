#include "tcppromotionlisthandler.h"
#include "sqlpromotionlistfinder.h"
#include "tcplocalresponse.h"
#include <QJsonArray>

TcpPromotionListHandler::TcpPromotionListHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpPromotionListHandler::handle(const TcpRequest &) {
    SqlPromotionListFinder promotionListFinder;
    QList<Promotion> promotionList = promotionListFinder.exec();
    QJsonArray promotionJsonArray;
    for (qsizetype i = 0; i < promotionList.count(); ++i) {
        promotionJsonArray.append(promotionList[i].toJson());
    }
    QJsonObject responseBody;
    responseBody["promotionList"] = promotionJsonArray;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find promotion list", responseBody);
    return response;
}
