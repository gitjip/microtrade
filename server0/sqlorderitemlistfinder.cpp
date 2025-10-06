#include "sqlorderitemlistfinder.h"
#include <QSqlError>

SqlOrderItemListFinder::SqlOrderItemListFinder() {}

QList<OrderItem> SqlOrderItemListFinder::exec(qint64 orderId) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM order_items WHERE order_id=:order_id AND "
                  "removed_at IS NULL");
    query.bindValue(":order_id", orderId);
    QList<OrderItem> orderItemList;
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    while (query.next()) {
        OrderItem orderItem{query.value("id").toLongLong(),
                            query.value("created_at").toDateTime(),
                            query.value("removed_at").toDateTime(),
                            query.value("order_id").toLongLong(),
                            query.value("product_id").toLongLong(),
                            query.value("quantity").toLongLong(),
                            query.value("cost").toDouble()};
        orderItemList.append(orderItem);
    }
    return orderItemList;
}
