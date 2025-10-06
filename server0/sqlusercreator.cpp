#include "sqlusercreator.h"
#include <QSqlError>

SqlUserCreator::SqlUserCreator() {}

User SqlUserCreator::exec(const User &user) {
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO users (created_at,username,password_hash,avatar_url) VALUES "
        "(:created_at,:username,:password_hash,:avatar_url)");
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":username", user.username());
    query.bindValue(":password_hash", user.passwordHash());
    query.bindValue(":avatar_url", user.avatarUrl().toString());
    qDebug() << "SqlUserCreator::exec:" << query.boundValueNames();
    qDebug() << "SqlUserCreator::exec:" << query.boundValues();
    if (!query.exec()) {
        qDebug() << "SqlUserCreator::exec:" << query.lastError().text();
        return {};
    }
    User returned{query.lastInsertId().toLongLong(), {}, {}, {}, {}};
    return returned;
}
