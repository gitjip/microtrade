#include "sqlcartcreator.h"
#include <QSqlError>

SqlCartCreator::SqlCartCreator() {}

bool SqlCartCreator::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO carts (user_id) VALUES (:user_id)");
    query.bindValue(":user_id", user.id());
    if (!query.exec()) {
        qDebug() << "SqlCartCreator::exec:" << query.lastError().text();
        return false;
    }
    qDebug() << "SqlCartCreator::exec:" << "success";
    return true;
}
