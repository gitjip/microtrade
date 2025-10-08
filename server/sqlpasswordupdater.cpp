#include "sqlpasswordupdater.h"
#include <QSqlError>

SqlPasswordUpdater::SqlPasswordUpdater() {}

bool SqlPasswordUpdater::exec(qint64 userId, const QString &oldPasswordHash,
                              const QString &newPasswordHash) {
    QSqlQuery query(db);
    query.prepare(
        "UPDATE users SET password_hash=:new_password_hash WHERE "
        "id=:id AND password_hash=:old_password_hash AND removed_at IS NULL");
    query.bindValue(":id", userId);
    query.bindValue(":old_password_hash", oldPasswordHash);
    query.bindValue(":new_password_hash", newPasswordHash);
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    }
    qDebug() << Q_FUNC_INFO << query.numRowsAffected();
    return query.numRowsAffected() > 0;
}
