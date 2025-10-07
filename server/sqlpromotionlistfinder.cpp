#include "sqlpromotionlistfinder.h"
#include <QSqlError>

SqlPromotionListFinder::SqlPromotionListFinder() {}

QList<Promotion> SqlPromotionListFinder::exec() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM promotions WHERE removed_at IS NULL AND "
                  "start_at<=:time AND end_at>=:time");
    query.bindValue(":time", QDateTime::currentDateTime());
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    QList<Promotion> promotionList;
    while (query.next()) {
        Promotion promotion {
            query.value("id").toLongLong(),
            query.value("created_at").toDateTime(),
            query.value("removed_at").toDateTime(),
            query.value("start_at").toDateTime(),
            query.value("end_at").toDateTime(),
            Promotion::stringToStrategy(query.value("strategy").toString()),
            query.value("threshold").toDouble(),
            query.value("value").toDouble()};
        promotionList.append(promotion);
        qDebug() << promotion.toJson();
    }
    return promotionList;
}
