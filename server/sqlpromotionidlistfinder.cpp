#include "sqlpromotionidlistfinder.h"
#include <QSqlError>

SqlPromotionIdListFinder::SqlPromotionIdListFinder() {}

QList<qint64> SqlPromotionIdListFinder::exec(qint64 productId) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product_promotion_relations WHERE "
                  "product_id=:product_id AND "
                  "removed_at IS NULL");
    query.bindValue(":product_id", productId);
    qDebug() << Q_FUNC_INFO << query.boundValueNames();
    qDebug() << Q_FUNC_INFO << query.boundValues();
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    QList<qint64> promotionList;
    while (query.next()) {
        qint64 promotionId = query.value("promotion_id").toLongLong();
        promotionList.append(promotionId);
        qDebug() << Q_FUNC_INFO << promotionId;
    }
    return promotionList;
}
