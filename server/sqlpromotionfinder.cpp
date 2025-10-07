#include "sqlpromotionfinder.h"
#include <QSqlError>

SqlPromotionFinder::SqlPromotionFinder() {}

Promotion SqlPromotionFinder::exec(qint64 promotionId) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM promotions WHERE id=:id AND removed_at IS NULL");
    query.bindValue(":id", promotionId);
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << Q_FUNC_INFO << "not found";
        return {};
    }
    Promotion promotion {
        query.value("id").toLongLong(),
        query.value("created_at").toDateTime(),
        query.value("removed_at").toDateTime(),
        query.value("start_at").toDateTime(),
        query.value("end_at").toDateTime(),
        Promotion::stringToStrategy(query.value("strategy").toString()),
        query.value("threshold").toDouble(),
        query.value("value").toDouble()};
    qDebug() << Q_FUNC_INFO << promotion.toJson();
    return promotion;
}
