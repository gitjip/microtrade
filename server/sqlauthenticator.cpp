#include "sqlauthenticator.h"
#include <QSqlError>

SqlAuthenticator::SqlAuthenticator() {}

User SqlAuthenticator::exec(const Authorization &authorization) {
    QSqlQuery query(db);
    query.prepare(
        "SELECT * FROM authorizations WHERE token=:token AND removed_at=NULL");
    query.bindValue(":token", authorization.token());
    if (!query.exec()) {
        qDebug() << "SqlAuthenticator::exec" << query.lastError().type()
                 << query.lastError().text();
        return {};
    }
    if (!query.next()) {
        qDebug() << "SqlAuthenticator::exec" << "not found";
        return {};
    }
    User user{query.value("user_id").toLongLong(), {}, {}, "", ""};
    qDebug() << "SqlAuthenticator::exec" << "success" << user.toJson();
    return user;
}
