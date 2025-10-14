#include "sqlorderitemcreator.h"
#include <QDateTime>
#include <QSqlError>

SqlOrderItemCreator::SqlOrderItemCreator() {}

qint64 SqlOrderItemCreator::exec(qint64 orderId, qint64 productId,
                                 qint64 quantity, double cost) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO order_items (created_at,order_id,product_id,quantity,cost) "
        "VALUES (:created_at,:order_id,:product_id,:quantity,:cost)");
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":order_id", orderId);
    query.bindValue(":product_id", productId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":cost", cost);
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toLongLong();
}
