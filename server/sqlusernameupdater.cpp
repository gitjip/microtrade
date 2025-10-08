#include "sqlusernameupdater.h"
#include <QSqlError>

SqlUsernameUpdater::SqlUsernameUpdater() {}

bool SqlUsernameUpdater::exec(qint64 userId, const QString &username) {
    QSqlQuery query(db);
    query.prepare("UPDATE users SET username=:username WHERE id=:id AND "
                  "removed_at IS NULL");
    query.bindValue(":username", username);
    query.bindValue(":id", userId);
    qDebug() << Q_FUNC_INFO << query.boundValueNames();
    qDebug() << Q_FUNC_INFO << query.boundValues();
    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    }
    qDebug() << Q_FUNC_INFO << "success";
    return true;
}
