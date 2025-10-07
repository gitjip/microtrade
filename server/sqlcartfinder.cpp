#include "sqlcartfinder.h"
#include "QSqlError"

SqlCartFinder::SqlCartFinder() {}

Cart SqlCartFinder::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM carts WHERE user_id=:user_id AND removed_at IS NULL");
    query.bindValue(":user_id", user.id());
    if (!query.exec()) {
        // qDebug() << "SqlCartFinder::exec:" << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        // qDebug() << "SqlCartFinder::exec:" << "not found";
        return {};
    }
    Cart cart{query.value("id").toLongLong(),
              query.value("created_at").toDateTime(),
              query.value("removed_at").toDateTime(),
              query.value("user_id").toLongLong()};
    // qDebug() << "SqlCartFinder::exec:" << "success:" << cart.toJson();
    return cart;
}
