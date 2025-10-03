#include "sqlloginchecker.h"
#include <QSqlError>
#include <QSqlQuery>

SqlLoginChecker::SqlLoginChecker() {}

User SqlLoginChecker::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username=:username AND "
                  "password_hash=:password_hash AND removed_at=NULL");
    query.bindValue(":username", user.username());
    query.bindValue(":password_hash", user.passwordHash());
    if (!query.exec()) {
        qDebug() << "SqlUserIdFinder::exec:" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlUserIdFinder::exec:" << "not found";
        return {};
    }
    User returned(query.value("id").toLongLong(), {}, {}, "", "");
    qDebug() << "SqlUserIdFinder::exec:" << "user_id:" << returned.id();
    return returned;
}
