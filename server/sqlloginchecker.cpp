#include "sqlloginchecker.h"
#include <QSqlError>
#include <QSqlQuery>

SqlLoginChecker::SqlLoginChecker() {}

User SqlLoginChecker::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username=:username AND "
                  "password_hash=:password_hash AND removed_at IS NULL");
    query.bindValue(":username", user.username());
    query.bindValue(":password_hash", user.passwordHash());
    qDebug() << "SqlLoginChecker::exec:" << query.boundValueNames();
    qDebug() << "SqlLoginChecker::exec:" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "SqlLoginChecker::exec:" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlLoginChecker::exec:" << "not found";
        return {};
    }
    User returned(query.value("id").toLongLong(), {}, {}, "", "");
    qDebug() << "SqlLoginChecker::exec:" << "user_id:" << returned.id();
    return returned;
}
