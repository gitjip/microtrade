#include "sqlusernameupdater.h"
#include <QSqlError>

SqlUsernameUpdater::SqlUsernameUpdater() {}

bool SqlUsernameUpdater::exec(qint64 userId, const QString &username) {
    QSqlQuery query(db);
    query.prepare("UPDATE users SET username=:username WHERE id=:id AND "
                  "removed_at IS NULL");
    query.bindValue(":username", username);
    query.bindValue(":id", userId);
    if (!query.exec()) {
        return false;
    }
    return true;
}
