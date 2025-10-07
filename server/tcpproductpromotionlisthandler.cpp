#include "tcpproductpromotionlisthandler.h"
#include "qjsonarray.h"
#include "sqlpromotionfinder.h"
#include "sqlpromotionidlistfinder.h"
#include "tcplocalresponse.h"

TcpProductPromotionListHandler::TcpProductPromotionListHandler(QObject *parent)
    : TcpHandler{parent} {}

TcpResponse TcpProductPromotionListHandler::handle(const TcpRequest &request) {
    QJsonObject requestBody = request.body();
    qint64 productId = requestBody["productId"].toInteger();
    SqlPromotionIdListFinder promotionIdListFinder;
    QList<qint64> promotionIdList = promotionIdListFinder.exec(productId);
    SqlPromotionFinder promotionFinder;
    QJsonArray promotionJsonArray;
    for (qsizetype i = 0; i < promotionIdList.count(); ++i) {
        Promotion promotion = promotionFinder.exec(promotionIdList[i]);
        promotionJsonArray.append(promotion.toJson());
    }
    QJsonObject responseBody;
    responseBody["promotionList"] = promotionJsonArray;
    TcpResponse response =
        TcpLocalResponse::make(true, TcpResponse::StatusType::Success,
                                                  "successfully find promotion list", responseBody);
    return response;
}
