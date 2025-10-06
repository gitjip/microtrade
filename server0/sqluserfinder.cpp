#include "sqluserfinder.h"
#include <QSqlError>

SqlUserFinder::SqlUserFinder() {}

User SqlUserFinder::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE id=:id AND removed_at IS NULL");
    query.bindValue(":id", user.id());
    if (!query.exec()) {
        qDebug() << "SqlUserFinder::exec:" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlUserFinder::exec:" << "not found";
        return {};
    }
    User returned{query.value("id").toLongLong(),
                  query.value("created_at").toDateTime(),
                  query.value("removed_at").toDateTime(),
                  query.value("username").toString(),
                  query.value("password_hash").toString(),
                  QUrl(query.value("avatar_url").toString())};
    qDebug() << "SqlUserFinder::exec:" << "find user:" << returned.toJson();
    return returned;
}
