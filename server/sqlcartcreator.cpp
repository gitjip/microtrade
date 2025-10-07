#include "sqlcartcreator.h"
#include <QSqlError>

SqlCartCreator::SqlCartCreator() {}

bool SqlCartCreator::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO carts (created_at,user_id) VALUES (:created_at,:user_id)");
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":user_id", user.id());
    // qDebug() << "SqlCartCreator::exec:" << query.boundValueNames();
    // qDebug() << "SqlCartCreator::exec:" << query.boundValues();
    if (!query.exec()) {
        // qDebug() << "SqlCartCreator::exec:" << query.lastError().text();
        return false;
    }
    // qDebug() << "SqlCartCreator::exec:" << "success";
    return true;
}
