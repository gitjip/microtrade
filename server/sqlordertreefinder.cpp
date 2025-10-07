#include "sqlordertreefinder.h"
#include <QSqlError>

SqlOrderTreeFinder::SqlOrderTreeFinder() {}

QMap<Order, QList<OrderItem>> SqlOrderTreeFinder::exec(qint64 userId) {
    // qDebug() << Q_FUNC_INFO << "userId:" << userId;
    QMap<Order, QList<OrderItem>> orderTree;
    QSqlQuery orderQuery(db);
    orderQuery.prepare(
        "SELECT * FROM orders WHERE user_id=:user_id AND removed_at IS NULL");
    orderQuery.bindValue(":user_id", userId);
    if (!orderQuery.exec()) {
        // qDebug() << Q_FUNC_INFO << "orderQuery" << orderQuery.lastError().text();
        return {};
    }
    // qDebug() << Q_FUNC_INFO << "orderQuery size:" << orderQuery.size();
    while (orderQuery.next()) {
        Order order{orderQuery.value("id").toLongLong(),
                    orderQuery.value("created_at").toDateTime(),
                    orderQuery.value("removed_at").toDateTime(),
                    orderQuery.value("user_id").toLongLong(),
                    orderQuery.value("cost").toDouble(),
                    Order::stringToStatus(orderQuery.value("status").toString())};
        qDebug() << Q_FUNC_INFO << "orderId:" << order.id();
    }
    // qDebug() << Q_FUNC_INFO << "orderQuery:" << orderTree.count();
    return orderTree;
}
