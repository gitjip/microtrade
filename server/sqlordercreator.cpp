#include "sqlordercreator.h"
#include "costcalculator.h"
#include "order.h"
#include <QSqlError>

SqlOrderCreator::SqlOrderCreator() {}

qint64 SqlOrderCreator::exec(const User &user,
                             const QMap<Product, qint64> &quantityMap) {
    double totalCost = CostCalculator::calculate(quantityMap);
    QSqlQuery query(db);
    query.prepare("INSERT INTO orders (created_at,user_id,cost,status) VALUES "
                  "(:created_at,:user_id,:cost,:status)");
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":user_id", user.id());
    query.bindValue(":cost", totalCost);
    query.bindValue(":status", Order::statusToString(Order::Status::Pending));
    if (!query.exec()) {
        // qDebug() << Q_FUNC_INFO << query.lastError().text();
        return -1;
    }
    // qDebug() << Q_FUNC_INFO << "success";
    return query.lastInsertId().toLongLong();
}
