#include "sqlauthenticator.h"
#include <QSqlError>

SqlAuthenticator::SqlAuthenticator() {}

User SqlAuthenticator::exec(const Authorization &authorization) {
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM authorizations WHERE token=:token AND removed_at IS NULL");
    query.bindValue(":token", authorization.token());
    // qDebug() << Q_FUNC_INFO << query.boundValueNames();
    // qDebug() << Q_FUNC_INFO << query.boundValues();
    if (!query.exec()) {
        // qDebug() << Q_FUNC_INFO << query.lastError().type()
        //          << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        // qDebug() << Q_FUNC_INFO << "not found";
        return {};
    }
    User user{query.value("user_id").toLongLong(), {}, {}, "", ""};
    // qDebug() << Q_FUNC_INFO << "success" << user.toJson();
    return user;
}
