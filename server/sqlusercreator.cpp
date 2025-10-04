#include "sqlusercreator.h"
#include <QSqlError>

SqlUserCreator::SqlUserCreator() {}

User SqlUserCreator::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username,password_hash,avatar_url) VALUES "
                  "(:username,:password_hash,:avatar_url)");
    query.bindValue(":username", user.username());
    query.bindValue(":password_hash", user.passwordHash());
    query.bindValue(":avatar_url", user.avatarUrl().toString());
    if (!query.exec()) {
        qDebug() << "SqlUserCreator::exec:" << query.lastError().text();
        return {};
    }
    User returned{query.lastInsertId().toLongLong(), {}, {}, {}, {}};
    return returned;
}
