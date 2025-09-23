#include "shopcontroller.h"
#include "goods.h"
#include <QPixmap>
#include <QSqlQuery>

namespace My {
ShopController::ShopController(QObject *parent)
    : Controller(parent) {}

Response ShopController::post(const Headers &headers, const Body &body) {
    Q_UNUSED(headers);
    QSqlQuery query(db);
    int goodsId = body.toInt();
    query.prepare("SELECT * FROM goods where rowid = :id");
    query.bindValue(":id", goodsId);
    if (!query.exec()) {
        qDebug() << "ShopController::post: error occurred when quering goods";
        return Response(500, Headers(), Body(),
                        "error occurred when quering goods");
    }
    if (!query.next()) {
        qDebug() << "ShopController::post: goods not found";
        return Response(404, Headers(), Body(), "goods not found");
    }
    Goods responseGoods(
        goodsId, query.value("name").toString(),
        query.value("description").toString(), query.value("price").toDouble(),
        query.value("stock").toInt(), query.value("category").toString());
    return Response(200, Headers(), QJsonObject(responseGoods), "");
}
} // namespace My
