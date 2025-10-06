#include "sqlorderlistfinder.h"
#include <QSqlError>

SqlOrderListFinder::SqlOrderListFinder() {}

QList<Order> SqlOrderListFinder::exec(qint64 userId) {
    qDebug() << Q_FUNC_INFO << "userId:" << userId;
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM orders WHERE user_id=:user_id AND removed_at IS NULL");
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return {};
    }
    QList<Order> orderList;
    while (query.next()) {
        Order order{query.value("id").toLongLong(),
                    query.value("created_at").toDateTime(),
                    query.value("removed_at").toDateTime(),
                    query.value("user_id").toLongLong(),
                    query.value("cost").toDouble(),
                    Order::stringToStatus(query.value("status").toString())};
        orderList.append(order);
    }
    return orderList;
}
