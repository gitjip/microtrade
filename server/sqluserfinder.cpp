#include "sqluserfinder.h"
#include <QSqlError>

SqlUserFinder::SqlUserFinder() {}

User SqlUserFinder::exec(const QString &userId) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE id=:id AND is_deleted=0");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        qDebug() << "SqlUserFinder::exec:" << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlUserFinder::exec:" << "not found";
        return {};
    }
    User user{query.value("id").toString(),
              query.value("username").toString(),
              query.value("password").toString(),
              QUrl(query.value("avatar_url").toString()),
              query.value("registered_at").toDateTime(),
              query.value("unregistered_at").toDateTime()};
    qDebug() << "SqlUserFinder::exec:" << "find user:" << QJsonObject(user);
    return user;
}
