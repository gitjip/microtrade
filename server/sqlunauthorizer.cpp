#include "sqlunauthorizer.h"
#include <QSqlError>

SqlUnauthorizer::SqlUnauthorizer() {}

bool SqlUnauthorizer::exec(const Authorization &authorization) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE authorizations SET removed_at=:removed_at WHERE token=:token");
    query.bindValue(":removed_at", QDateTime::currentDateTime());
    query.bindValue(":token", authorization.token());
    // qDebug() << "SqlUnauthorizer::exec:" << query.boundValueNames();
    // qDebug() << "SqlUnauthorizer::exec:" << query.boundValues();
    if (!query.exec()) {
        // qDebug() << "SqlUnauthorizer::exec:" << query.lastError().text();
        return false;
    }
    return true;
}
